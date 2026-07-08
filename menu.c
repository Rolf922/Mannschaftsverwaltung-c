#include <stdio.h>
#include <string.h>
#include "menu.h"
#include "tools.h"

/***************************************************************
 * Funktion: getMenu
 * Beschreibung: Anzeigen des Menus und Ruckgabe der vom Benutzer eingegebenen Wahl
 * Parameter:
 *      title     - title of the menu
 *      menuItems - array mit den Menueintragen
 *      itemCount - anzahl der Eintrage im Menu
 * Return:
 *      wahle die Nummer des ausgewahlten Menu aus
 ***************************************************************/

int getMenu(char *title, char *menuItems[], int itemCount)
{
    int choice = 0;
    int i;

    do
    {
        clearScreen();

        printf("%s\n", title);
        printLine('=', strlen(title));

        for (i=0; i<itemCount; i++)
        {
            printf("%d. %s\n", i+1, menuItems[i]);
        }

        printf("\nIhre Wahl: ");
        scanf("%d", &choice);
        clearBuffer();

    } while (choice < 1 || choice > itemCount);

    return choice;
}
