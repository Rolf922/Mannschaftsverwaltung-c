#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"
#include "datastructure.h"
#include "tools.h"

#define MAX_LINE_LENGTH 101

static void saveTeam(FILE *file, sTeam *team);
static void savePlayer(FILE *file, sPlayer *player);

static void loadTeam(FILE *file, sTeam *team);
static void loadPlayer(FILE *file, sPlayer *player);

static char *skipSpaces(char *line);
static int readTextTag(char *line, char *startTag, char *endTag, char **target);
static int readNumberTag(char *line, char *startTag, char *endTag);
static void readDateTag(char *line, sPlayer *player);
static void skipUntil(FILE *file, char *endTag);

const char *filename="teams.xml";


/*************************************************
 * Funktion zum Speichern aller Daten in eine Datei
 *Sie macht Folgendes
 *Datei öffnen
 *<Data> schreiben
 *alle Mannschaften durchgehen
 *für jede Mannschaft saveTeam aufrufen
 *</Data> schreiben
 *Datei schließen
*************************************************/
sTeam *FirstTeam = NULL;
sTeam *LastTeam = NULL;
int Teamcounter = 0;





void save(const char *filename)
{
    FILE *file;
    int i;

    file = fopen(filename, "w");

    if (file != NULL)
    {
        fprintf(file, "<Data>\n");

        for (i = 0; i < Teamcounter; i++)
        {
            saveTeam(file, Teams + i);
        }

        fprintf(file, "</Data>\n");

        fclose(file);
    }
}


/******************************************************
 *Diese Funktion speichert eine einzelne Mannschaft  in
 *eine Datei.
******************************************************/

void saveTeam(FILE *file, sTeam *team)
{
    int i;

    fprintf(file, " <Team>\n");

    if (team->teamname != NULL)
    {
        fprintf(file, "  <Name>%s</Name>\n", team->teamname);
    }

    if (team->trainername != NULL)
    {
        fprintf(file, "  <Trainer>%s</Trainer>\n", team->trainername);
    }
    else
    {
        fprintf(file, "  <Trainer></Trainer>\n");
    }

    for (i = 0; i < team->playercount; i++)
    {
        savePlayer(file, team->players + i);
    }

    fprintf(file, " </Team>\n");
}


/******************************************************************
 *Diese Funktion speichert einen Spieler in eine Datei
 *****************************************************************/

void savePlayer(FILE *file, sPlayer *player)
{
    fprintf(file, "  <Player>\n");

    if (player->playername != NULL)
    {
        fprintf(file, "   <Name>%s</Name>\n", player->playername);
    }

    if (player->birthday != NULL)
    {
        fprintf(file,
                "   <Birthday>%02d.%02d.%04d</Birthday>\n",
                player->birthday->Day,
                player->birthday->Month,
                player->birthday->Year);
    }

    fprintf(file, "   <TricotNr>%d</TricotNr>\n", player->shirtnumber);
    fprintf(file, "   <Goals>%d</Goals>\n", player->goals);

    fprintf(file, "  </Player>\n");
}

/**********************************************************************
 *Diese Funktion lädt alle Daten aus der Datei.
 *Sie macht Folgendes
 *Datei öffnen
 *Zeile für Zeile lesen
 *wenn <Team> gefunden wird:
    *loadTeam aufrufen
 *Datei schließen
***********************************************************************/

void load(const char *filename)
{
    FILE *file;
    char line[500];
    char *content;

    file = fopen(filename, "r");

    if (file != NULL)
    {
        while (fgets(line, 500, file) != NULL)
        {
            content = skipSpaces(line);  //Hilfsfunktion, die Leerzeichen am Anfang der Zeile ueberspringt

            if (strncmp(content, "<Team>", 6) == 0)
            {
                if (Teamcounter < MAXTEAMS)
                {
                    loadTeam(file, Teams + Teamcounter);
                    Teamcounter++;
                }
            }
        }

        fclose(file);
    }
}

/*****************************************************
 *diese Funktion laedt eine Mannschaft
*****************************************************/
void loadTeam(FILE *file, sTeam *Team)
{
    char line[500];
    char *content;

    Team->teamname = NULL;
    Team->trainername = NULL;
    Team->playercount = 0;

    while (fgets(line, 500, file) != NULL)
    {
        content = skipSpaces(line);

        if (strncmp(content, "</Team>", 7) == 0)
        {
            return;
        }
        else if (strncmp(content, "<Name>", 6) == 0)
        {
            readTextTag(content, "<Name>", "</Name>", &(Team->teamname));
        }
        else if (strncmp(content, "<Trainer>", 9) == 0)
        {
            readTextTag(content, "<Trainer>", "</Trainer>", &(Team->trainername));
        }
        else if (strncmp(content, "<Player>", 8) == 0)
        {
            if (Team->playercount < MAXPLAYER)
            {
                loadPlayer(file, Team->players + Team->playercount);
                Team->playercount++;
            }
            else
            {
                skipUntil(file, "</Player>");
            }
        }
    }
}

/******************************************************************************
 *Diese Funktion laedt einen Player
******************************************************************************/
void loadPlayer(FILE *file, sPlayer *player)
{
    char line[500];
    char *content;

    player->playername = NULL;
    player->birthday = NULL;
    player->shirtnumber = 0;
    player->goals = 0;

    while (fgets(line, 500, file) != NULL)
    {
        content = skipSpaces(line);

        if (strncmp(content, "</Player>", 9) == 0)
        {
            return;
        }
        else if (strncmp(content, "<Name>", 6) == 0)
        {
            readTextTag(content, "<Name>", "</Name>", &(player->playername));
        }
        else if (strncmp(content, "<Birthday>", 10) == 0)
        {
            readDateTag(content, player);
        }
        else if (strncmp(content, "<TricotNr>", 10) == 0)
        {
            player->shirtnumber = readNumberTag(content, "<TricotNr>", "</TricotNr>");
        }
        else if (strncmp(content, "<Goals>", 7) == 0)
        {
            player->goals = readNumberTag(content, "<Goals>", "</Goals>");
        }
    }
}

char *skipSpaces(char *line)
{
    while ((*line == ' ') || (*line == '\t'))
    {
        line++;
    }

    return line;
}

int readTextTag(char *line, char *startTag, char *endTag, char **target)
{
    char *start;
    char *end;
    int length;

    if ((line == NULL) || (startTag == NULL) || (endTag == NULL) || (target == NULL))
    {
        return 0;
    }

    start = strstr(line, startTag);

    if (start == NULL)
    {
        return 0;
    }

    start = start + strlen(startTag);

    end = strstr(start, endTag);

    if (end == NULL)
    {
        return 0;
    }

    length = end - start;

    if (*target != NULL)
    {
        free(*target);
        *target = NULL;
    }

    *target = malloc((length + 1) * sizeof(char));

    if (*target == NULL)
    {
        return 0;
    }

    strncpy(*target, start, length);
    *(*target + length) = '\0';

    return 1;
}

int readNumberTag(char *line, char *startTag, char *endTag)
{
    char *text = NULL;
    int number = 0;

    if (readTextTag(line, startTag, endTag, &text))
    {
        number = atoi(text);
        free(text);
    }

    return number;
}

void readDateTag(char *line, sPlayer *player)
{
    char *text = NULL;
    int Day;
    int Month;
    int Year;
    sDate *date;

    if (player == NULL)
    {
        return;
    }

    if (readTextTag(line, "<Birthday>", "</Birthday>", &text))
    {
        if (sscanf(text, "%d.%d.%d", &Day, &Month, &Year) == 3)
        {
            if (player->birthday != NULL)
            {
                free(player->birthday);
                player->birthday = NULL;
            }

            date = malloc(sizeof(sDate));

            if (date != NULL)
            {
                date->Day = Day;
                date->Month = Month;
                date->Year = Year;

                player->birthday = date;
            }
        }

        free(text);
    }
}

void skipUntil(FILE *file, char *endTag)
{
    char line[MAX_LINE_LENGTH];
    char *content;

    if ((file == NULL) || (endTag == NULL))
    {
        return;
    }

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL)
    {
        content = skipSpaces(line);

        if (strncmp(content, endTag, strlen(endTag)) == 0)
        {
            return;
        }
    }
}

