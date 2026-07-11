#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED

#include "datastructure.h"

// vergleichsfunktion nach Namen
int compareByName(const void *a, const void *b);

// Vergleichsfunktion nach Geburtsdatum
int compareByBirthdate(const void *a, const void *b);

// Vergleichsfunktion nach Shirtnumber
int compareByJerseyNumber(const void *a, const void *b);

// Vergleichsfunktion nach Toranzahl
int compareByGoals(const void *a, const void *b);

// Funktion zum schnellen Vergleich der Spieler von einer Manschaft
void quickSort(sPlayer *players,int low,int high,int (*compare)(const void *, const void *));

#endif
