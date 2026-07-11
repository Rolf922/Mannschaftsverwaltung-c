#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "datastructure.h"
#include "tools.h"
#include "menu.h"
#include "sort.h"
#include "datetime.h"
#include "teams.h"

/* globale Variable */
sTeam *FirstTeam = NULL;
sTeam *LastTeam = NULL;
int Teamcounter = 0;

/***************************************************************
* Function: createTeam
* Description: Funktion zur Erstellung einer neuen Mannschaft.
***************************************************************/
int createTeam()
{
    sTeam *Team = malloc(sizeof(sTeam));
    if(!(getText("teamname eingeben:", 50, 0, &Team->teamname)))
    {
        printf("ungueltiger TeamName.\n");
        return 0;
    }

    // Trainername eingeben (optional)
    printf("Trainername eingeben (optional): ");
    char trainername[50];
    fgets(trainername, sizeof(trainername), stdin);
    if (trainername[0] != '\n') {
        Team->trainername = malloc(strlen(trainername) + 1);
        strcpy(Team->trainername, trainername);
    } else {
        Team->trainername = NULL;
    }

    // Playeranzahl initialisieren
    Team->playercount = 0;

    // schleife zum Hinzufugen von Playern
    do
    {
        if (createPlayer(Team->players + Team->playercount))
        {
            Team->playercount++;
        }
        else
        {
            printf("Player konnte nicht hinzugefugt werden.\n");
        }

    } while ((Team->playercount < MAXPLAYER) && askYesOrNo("Moechten Sie einen weiteren Player hinzufugen ?"));

    Teamcounter++;

    return 1;
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
    int choice;
    char *menuoptions[] = {
        "Spieler nach Namen sortieren",
        "Spieler nach Geburtsdatum (Alter) sortieren",
        "Spieler nach Trikotnr. Sortieren",
        "Spieler nach Anzahl geschossener Tore sortieren",
        "zurueck zum Hauptmenue"
    };
    int menuoptioncount = sizeof(menuoptions) / sizeof(menuoptions[0]);

    // Display the sorting submenu
    choice = getMenu("Untermenü für die Sortierung", menuoptions, menuoptioncount);
    printf("Benutzer hat die Option gewaehlt: %d\n", choice);
    sTeam *current = FirstTeam; // start from the first team

    while (current!= NULL && Teamcounter!=0){
    switch (choice) {
        case 1:
            printf("Sortieren nach Namen...\n");
            quickSort((*current)players, 0, current->playercount - 1, compareByName);
            break;

        case 2:
            printf("Sortieren nach Geburtsdatum...\n");
            quickSort((*current)players, 0, current->playercount - 1, compareByName);
            break;

        case 3:
            printf("Sortieren nach Trikotnummer ...\n");
            quickSort((*current)players, 0, current->playercount - 1, compareByName);
            break;

        case 4:
            printf("Sortieren nach Anzahl geschossener Tore ...\n");
            quickSort((*current)players, 0, current->playercount - 1, compareByName);
            break;

        case 5:
            printf("Zurueck zum Hauptmenu\n");
            break;

        default:
            printf("ungueltige Auswahl!\n");
            return;
    }
    current = current->next; //geht zum naechsten Team
    }
    printf("\n Sortierung abgeschlossen.Sortierte Liste:\n");
    listTeams();



    //printf("sortTeams\n");
    //waitForEnter();
}


/***************************************************************
 * Function: listTeams
 * Description: gibt alle Mannschaften aus
 ***************************************************************/
void listTeams(void)
{
    printf("liste der Mannschaften\n");
    printf("======================\n\n");

    if (FirstTeam ==NULL)
        printf("keine Mannschaften vorhanden\n");

        sTeam *current = FirstTeam;
        int index = 1;
        while (current != NULL) {
            listOneTeam(current, index);
            printf("\n");
            current = current->next;
            index ++;
        }

        waitForEnter();
    //for (int i = 0; i < Teamcounter; i++) {
      //  listOneTeam(Teams + i);
        //printf("\n");
    //}

    // waitForEnter();
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

// Funktion zum Loeschen einer Mannschaft aus der Liste

void deleteTeam() {
    sTeam *current = FirstTeam;
    sTeam *teamtodelete = NULL;
    int choice, index = 1;

    if (current == NULL) {
        printf("keine Mannschaften zum loeschen vorhanden.\n");
        return;
    }
    //  Display teams with numbers for deletion
    printf("Auswahl einer Mannschaft zum Loeschen:\n");
    printf("Liste der Mannschaften\n");
    printf("=======================\n\n");

    while (current != NULL) {
        printf("%d: %s\n", index, current->teamname);
        current = current->next;
        index++;
    }

    printf ("welche Mannschaft moechten Sie loeschen(0 fuer Abbrechen)?");
    scanf("%d", &choice);

    if (choice == 0) {
        printf("Loeschen abgebrochen.\n");
        return;
    }

    current = FirstTeam;
    index = 1;
    while (current != NULL) {
        if (index == choice) {
            teamtodelete = current;
            break;
        }
        current = current->next;
        index++;
    }

    if (teamtodelete != NULL) {
        // Loescht ein team aus der Liste
        removeDListElement(teamtodelete);

        // gibt der Speicher frei fuer teamname, trainername....
        free(teamtodelete->teamname);
        free(teamtodelete->trainername);

        for (int i = 0; i < teamtodelete->playercount;i++) {
            free(teamtodelete->players[i].playername);
            free(teamtodelete->players[i].birthday);
        }

        free(teamtodelete);
        Teamcounter--;
        printf("Mannschaft erfolgreich geloescht. \n");
    }else{
        printf("ungueltige Auswahl. Mannschaft konnte nicht gefunden werden\n");
    }
}


