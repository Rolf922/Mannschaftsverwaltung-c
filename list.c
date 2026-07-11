#include <stdio.h>
#include <string.h>
#include "list.h"

#include "datastructure.h"
#include "teams.h"



/**************************************************************************************************************************
int compareTeams(const char *a, const char *b) {

    return strcmp(a,b);

}

// Funktion zu insert the doubleverkettete Liste, return 1 im Erfolg

int insertDListElement(sTeam *newTeam)
{
    //struct ListElement *New = NULL;

    //New = malloc(sizeof(struct ListElement));
    //if (New != NULL)
    //{
        //New-> Index = NewIndex;
        //New-> Value = NewValue;
        //New-> prev = NULL;
        //New-> next = NULL;
        if (FirstTeam = NULL)
        {
            /* liste ist noch leer
            FirstTeam = LastTeam = newTeam;
        }
****************************************************************************************************************

        // Initialize newTeam pointers
        newTeam->next = NULL;
        newTeam->next = NULL;

        sTeam *current = FirstTeam;
        /* while (current != NULL && compareTeams(current->pTeamName, teamName) < 0) {
        current = current->next;
        }

        if (strcmp(newTeam->teamname,FirstTeam->teamname)<=0 /*current = FirstTeam) {

            // Einfugen am Anfang
            newTeam->next = FirstTeam;
            FirstTeam->prev = newTeam;
            FirstTeam = newTeam;
        } else if (strcmp(newTeam->teamname, FirstTeam->teamname)>0 /*current == NULL) {

            // Insert at the End
            LastTeam->next = newTeam;
            newTeam->prev = LastTeam;
            LastTeam = newTeam;
        } else {
            // Insert in the middle
            newTeam->next = current;
            newTeam->prev = current->prev;
            current->prev ->next = newTeam;
            current->prev = newTeam;
        }
        return 1; // Return 1 for success
}

// Funktion zum Loeschen des Teams aus der Liste, return der Liste aus der Kommando free





        //else
        //{
          //  /* Liste ist nicht leer
            //LastTeam ->next = New;
            //New-> prev = LastTeam;
            //LastTeam = New;
        //}
        //return Index;
    //}
    //return 0;
//}
***********************************************************************************************************************/




/****************************************************************************************************************************
*************Die Aufgabe faengt hier an
****************************************************************************************************************************/



/**********************************************************
 * Funktion: insertDListElement
 *
 * Beschreibung:
 * Fuegt eine Mannschaft sortiert in die doppelt verkettete
 * Liste ein. Die Sortierung erfolgt mit Hilfe der uebergebenen
 * Vergleichsfunktion compare.
 *
 * Parameter:
 * newTeam - Zeiger auf die neue Mannschaft
 * compare - Vergleichsfunktion fuer zwei Mannschaften
 *
 * Rueckgabewert:
 * keiner
 **********************************************************/
void insertDListElement(sTeam *newTeam,
                        int (*compare)(sTeam *, sTeam *))
{
    sTeam *current;

    if ((newTeam == NULL) || (compare == NULL))
    {
        return;
    }

    newTeam->next = NULL;
    newTeam->prev = NULL;

    /*
     * Fall 1:
     * Die Liste ist noch leer.
     */
    if (FirstTeam == NULL)
    {
        FirstTeam = LastTeam = newTeam;
        return;
    }

    /*
     * Fall 2:
     * Neues Element muss vor das erste Element.
     */
    if (compare(newTeam, FirstTeam) < 0)
    {
        newTeam->next = FirstTeam;
        FirstTeam->prev = newTeam;
        FirstTeam = newTeam;
        return;
    }

    /*
     * Fall 3:
     * Richtige Position in der Liste suchen.
     */
    current = FirstTeam;

    while ((current->next != NULL) &&
           (compare(newTeam, current->next) >= 0))
    {
        current = current->next;
    }

    /*
     * Fall 4:
     * Neues Element hinter current einfuegen.
     */
    newTeam->next = current->next;
    newTeam->prev = current;

    if (current->next != NULL)
    {
        current->next->prev = newTeam;
    }
    else
    {
        LastTeam = newTeam;
    }

    current->next = newTeam;
}

/**********************************************************
 * Funktion: removeDListElement
 *
 * Beschreibung:
 * Entfernt eine Mannschaft aus der doppelt verketteten Liste.
 * Der Speicher der Mannschaft wird hier NICHT freigegeben.
 * Das Freigeben soll danach in teams.c passieren.
 *
 * Parameter:
 * team - Zeiger auf die zu entfernende Mannschaft
 *
 * Rueckgabewert:
 * keiner
 **********************************************************/
void removeDListElement(sTeam *team)
{
    if (team == NULL)
    {
        return;
    }

    /*
     * Wenn es ein vorheriges Element gibt,
     * wird dessen next-Zeiger angepasst.
     * Sonst war team das erste Element.
     */
    if (team->prev != NULL)
    {
        team->prev->next = team->next;
    }
    else
    {
        FirstTeam = team->next;
    }

    /*
     * Wenn es ein naechstes Element gibt,
     * wird dessen prev-Zeiger angepasst.
     * Sonst war team das letzte Element.
     */
    if (team->next != NULL)
    {
        team->next->prev = team->prev;
    }
    else
    {
        LastTeam = team->prev;
    }

    /*
     * Das entfernte Element von der Liste trennen.
     */
    team->next = NULL;
    team->prev = NULL;
}
