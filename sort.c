#include "sort.h"
#include <string.h>
#include "datastructure.h"
#include "teams.h"

// vergleichsfunktion nach Namen
int compareByName(const void *a, const void *b) {
    sPlayer *playerA = (sPlayer *)a;
    sPlayer *playerB = (sPlayer *)b;

    return strcmp(playerA->playername, playerB->playername);
}

// Vergleichsfunktion nach Geburtsdatum
int compareByBirthdate(const void *a, const void *b) {
    sPlayer *playerA = (sPlayer *)a;
    sPlayer *playerB = (sPlayer *)b;
        // ueberprefe, ob dasGeburtsdatum eines Players gultig ist
    if (playerA->birthday==NULL) {
        return -1;
    }

    if (playerB->birthday==NULL) {
        return 1;
    }
    if (playerA->birthday->Year != playerB->birthday->Year)
        return playerA->birthday->Year - playerB->birthday->Year;
    if (playerA->birthday->Month != playerB->birthday->Month)
        return playerA->birthday->Month - playerB->birthday->Month;
    return playerA->birthday->Day - playerB->birthday->Day;
}

// Vergleichsfunktion nach Shirtnumber
int compareByJerseyNumber(const void *a, const void *b) {
    sPlayer *playerA = (sPlayer *)a;
    sPlayer *playerB = (sPlayer *)b;
    return playerA->shirtnumber - playerB->shirtnumber;
}

// Vergleichsfunktion nach Toranzahl
int compareByGoals(const void *a, const void *b) {
    sPlayer *playerA = (sPlayer *)a;
    sPlayer *playerB = (sPlayer *)b;
    if (playerA->goals != playerB->goals)
        return playerA->goals - playerB->goals;
    return strcmp(playerA->playername, playerB->playername); // Tie-breaking by name
}
// Quicksort function
void quickSort(sPlayer *players, int low, int high, int (*compare)(const void *, const void *)) {
    int partition(sPlayer *players, int low, int high, int (*compare)(const void *, const void *));//Declaration of Partition
    if (low < high) {
        int pivot = partition(players, low, high, compare);
        quickSort(players, low, pivot - 1, compare);
        quickSort(players, pivot + 1, high, compare);
    }
}

// Partition function for quicksort
int partition(sPlayer *players, int low, int high, int (*compare)(const void *, const void *)) {
    //sPlayer *pivot = (players + low);

    //Function Swap (defining a=b and b=a)
    void swap(sPlayer *a, sPlayer *b)
    {
        sPlayer temp=*a;
        *a = *b;
        *b = temp;
    }

    //Versteckte Bubble Sort
    /*int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (compare(&players[j], &pivot) <= 0) {
            i++;
            sPlayer temp = players[i];
            *(players+i) = *(players+j);
            players[j] = temp;
        }
    }
    sPlayer temp = players[i + 1];
    players[i + 1] = players[high];
    players[high] = temp;
    return i + 1;*/

    //Quicksort
    int i = low + 1;
    int j = high; //
    sPlayer *comp= players+low; //zu vergleichenden Player (player b)
    while (i <= j) {

        while ((i <= j) && (compare(&players[i], comp) <= 0)) {
            i++;
        }

        while ((i <= j) && (compare(&players[j], comp) >= 0)) {
            j--;
        }

        if (i<j)//wenn i kleiner j
        {
            swap((players+i),(players+j));
            i++;
            j--;
        }
    }
    i--;
    swap((players+i),comp); //letzte stueck mit "zu vergleichenden" tauschen
    return i;
}
