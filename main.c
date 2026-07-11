#include <stdio.h>
#include "datastructure.h"
#include "tools.h"
#include "menu.h"
#include "teams.h"
#include "database.h"

/***************************************************************
 * Funktion: main
 * Beschreibung:
 * Startet das Programm. In einer Schleife wird das Hauptmenü
 * angezeigt. Der Benutzer kann eine Funktion auswählen. Erst wenn
 * der Benutzer den Menüpunkt "Programm beenden" auswählt, wird die
 * Schleife verlassen und das Programm beendet.
 *
 * Parameter:
 * keine
 *
 * Rückgabewert:
 * 0, wenn das Programm korrekt beendet wurde
 ***************************************************************/
int main(void)
{
    load("teams.xml");
    /* Titel des Hauptmenüs */
    char *menuTitle = "Mannschaften-Verwaltung V0.4";

    /* Texte der einzelnen Menüpunkte */
    char *menuItems[] =
    {
        "Neue Mannschaft anlegen",
        "Mannschaft loeschen",
        "Suchen",
        "Sortieren",
        "Auflisten",
        "Programm beenden"
    };

    /* Speichert die Auswahl des Benutzers */
    int choice;

    /* Anzahl der Menüpunkte im Hauptmenü */
    int itemCount = 6;

    /*
     * Das Menü wird so lange angezeigt, bis der Benutzer
     * den Menüpunkt 6 "Programm beenden" auswählt.
     */
    do
    {
        /* Menü anzeigen und Auswahl des Benutzers speichern */
        choice = getMenu(menuTitle, menuItems, itemCount);

        /*
         * Je nach Benutzerauswahl wird die entsprechende
         * Funktion aus dem Modul teams.c aufgerufen.
         */
        switch (choice)
        {
            case 1:
                /* Neue Mannschaft anlegen */
                createTeam();
                break;

            case 2:
                /* Mannschaft löschen */
                deleteTeam();
                break;

            case 3:
                /* Spieler suchen */
                searchPlayer();
                break;

            case 4:
                /* Mannschaften sortieren */
                sortTeams();
                break;

            case 5:
                /* Mannschaften auflisten */
                listTeams();
                break;

            case 6:
                /* Programm beenden */
                break;
        }

    } while (choice != 6);

    /* Daten beim Ende des Programms speichern */
    save("teams.xml");

    /* Programm erfolgreich beenden */
    return 0;
}
