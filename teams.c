#include <stdio.h>
#include <stdlib.h>
#include "datastructure.h"
#include "tools.h"
#include "datetime.h"
#include "teams.h"

/* globale Variable */
int Teamcounter = 0;
sTeam Teams[MAXTEAMS];

/***************************************************************
* Function: createTeam
* Description: Funktion zur Erstellung einer neuen Mannschaft.
***************************************************************/
void createTeam(void)
{
    sTeam *team = Teams + Teamcounter;
    if(!(getText("teamname eingeben:", 50, 0, &team->teamname)))
    {
        printf("ungueltiger TeamName.\n");
        return;
    }

    // Playeranzahl initialisieren
    team->playercount=0;

    // schleife zum Hinzufugen von Playern
    do{
        if (createPlayer(team->players + team->playercount)) {
            team->playercount++;
        } else{
            printf("Player konnte nicht hinzugefugt werden.\n");
        }

    } while (team->playercount < MAXPLAYER && askYesOrNo("Moechten Sie einen weiteren Player hinzufugen ?"));

    Teamcounter++;
}

/***************************************************************
*Funktion zur Ausgabe eines Players
***************************************************************/
void listOnePlayer(sPlayer *Player, int Nr) {
    printf("%02d. %s (%d", Nr, Player->playername, Player->shirtnumber);

    // print das Geburtsdatum, fals das existiert
    if(Player->birthday != NULL) {
        printf("; ");
        printDate(Player->birthday);
    }

    printf(")\n");
}




/***************************************************************
 * Function: deleteTeam
 * Description: Prints the function name and waits for Enter.
 ***************************************************************/
void deleteTeam(void)
{
    printf("deleteTeam\n");
    waitForEnter();
}


/***************************************************************
 * Function: searchPlayer
 * Description: Prints the function name and waits for Enter.
 ***************************************************************/
void searchPlayer(void)
{
    printf("searchPlayer\n");
    waitForEnter();
}

/***************************************************************
 * Function: sortTeams
 * Description: Prints the function name and waits for Enter.
 ***************************************************************/
void sortTeams(void)
{
    printf("sortTeams\n");
    waitForEnter();
}


/***************************************************************
 * Function: listTeams
 * Description: gibt alle Mannschaften aus
 ***************************************************************/
void listTeams(void)
{
    printf("liste der Mannschaften\n");
    printf("======================\n\n");

    if (Teamcounter ==0)
        printf("keine Mannschaften vorhanden\n");

    for (int i = 0; i < Teamcounter; i++) {
        listOneTeam(Teams + i);
        printf("\n");
    }

    waitForEnter();
}

/****************************************************************
*Funktion zur Ausgabe einer Mannschaft
****************************************************************/
void listOneTeam(sTeam *Team){
    printf("Name\t\t:%s\n", Team->teamname ? Team->teamname : "<kein Name>");
    printf("Anzahl der Players\t: %d\n", Team->playercount);

    printf("Player:\n");

    for(int i = 0; i < Team->playercount; i++) {
        listOnePlayer(Team->players + i, i + 1);
    }

}

/************ Funktion zur Eingabe eines neuen Spielers ***************/
int createPlayer(sPlayer *Player) {
    // Spielername eingeben
    getText("Playername eingeben: ", 50, 0, &Player->playername);
    /*if (!getText("Spielername eingeben: ", 50, 0, &spieler->pName)) {
        printf("Ungültiger Spielername.\n");
        return 0;
    }*/

    // Geburtsdatum des Spielers eingeben (optional)
    /*printf("Geburtsdatum des Spielers eingeben (optional, Format tt.mm.jjjj): ");
    char geburtsdatum[11];
    fgets(geburtsdatum, sizeof(geburtsdatum), stdin);
    if (geburtsdatum[0] != '\n') {
        spieler->Geburtsdatum = malloc(sizeof(sDate));
        sscanf(geburtsdatum, "%d.%d.%d", &spieler->Geburtsdatum->Day, &spieler->Geburtsdatum->Month, &spieler->Geburtsdatum->Year);
    } else {
        spieler->Geburtsdatum = NULL;
    }*/

    sDate date;
    char input[20];
    do
    {
        printf("Geburtsdatum des Players eingeben (optional, Format tt.mm.jjjj): ");
        *input = '\0';
        scanf("%19[^\n]", input);
        clearBuffer();

        if (input[0] == '\0')
        {
            Player->birthday = NULL;
            break;
        }

        if (getDateFromString(input, &date))
        {
            Player->birthday = malloc(sizeof(sDate));
            if (Player->birthday)
                *(Player->birthday) = date;
            break;
        }
        else
        {
            printf("Das eingegebene Datum '%s' ist ungueltig!\n", input);
            Player->birthday = NULL;
        }

    }while(1);


    // Trikotnummer des Players eingeben
    getNumber("Trikotnummer eingeben: ", &Player->shirtnumber, 1, 99);

    // Tore initial auf 0 setzen
    Player->goals = 0;

    return 1;
}

