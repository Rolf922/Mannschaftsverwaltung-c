#include <stdio.h>
#include <stdlib.h>
#include "datetime.h"

/********************************************************************
 * Funktion: int isLeapYear(int Year)
 * - Prueft, ob ein Jahr ein Schaltjahr ist.
 * Parameter:
 *   Year - zu pruefendes Jahr
 * Funktionsergebnis:
 *   1 = Schaltjahr
 *   0 = kein Schaltjahr
 *******************************************************************/
int isLeapYear(int Year)
{
    if (Year % 400 == 0)
        return 1;
    else if (Year % 100 == 0)
        return 0;
    else if (Year % 4 == 0)
        return 1;
    else
        return 0;
}

/********************************************************************
 * Funktion: int isDateValid(sDate Date)
 * - Prueft, ob ein Datum gueltig ist.
 * - Beruecksichtigt Monatsgrenzen und Schaltjahre.
 * Parameter:
 *   Date - zu pruefendes Datum
 * Funktionsergebnis:
 *   1 = Datum ist gueltig
 *   0 = Datum ist ungueltig
 *******************************************************************/
int isDateValid(sDate Date)
{
    int MaxDay;

    if (Date.Year < 1)
        return 0;

    if (Date.Month < 1 || Date.Month > 12)
        return 0;

    switch (Date.Month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            MaxDay = 31;
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            MaxDay = 30;
            break;

        case 2:
            if (isLeapYear(Date.Year))
                MaxDay = 29;
            else
                MaxDay = 28;
            break;

        default:
            return 0;
    }

    if (Date.Day < 1 || Date.Day > MaxDay)
        return 0;

    return 1;
}

/********************************************************************
 * Funktion: int getDateFromString(char *Input, sDate *Date)
 * - Zerlegt eine Zeichenkette in Tag, Monat und Jahr.
 * - Erwartet drei durch Punkte getrennte Zahlen.
 * - Die Punkte muessen nicht an festen Positionen stehen.
 * - Das geparste Datum wird auf Gueltigkeit geprueft.
 * Parameter:
 *   Input - Eingabezeichenkette
 *   Date  - Zeiger auf Datumsstruktur
 * Funktionsergebnis:
 *   1 = gueltiges Datum gefunden
 *   0 = ungueltig
 *******************************************************************/
int getDateFromString(char *Input, sDate *Date)
{
    int i;
    int Number;
    int Part;
    sDate TempDate;

    TempDate.Day = 0;
    TempDate.Month = 0;
    TempDate.Year = 0;

    Number = 0;
    Part = 0;
    i = 0;

    if (Input[0] == '\0')
        return 0;

    while (Input[i] != '\0')
    {
        if (Input[i] >= '0' && Input[i] <= '9')
        {
            Number = Number * 10 + (Input[i] - '0');
        }
        else if (Input[i] == '.')
        {
            if (Part == 0)
                TempDate.Day = Number;
            else if (Part == 1)
                TempDate.Month = Number;
            else
                return 0;

            Part++;
            Number = 0;
        }
        else
        {
            return 0;
        }

        i++;
    }

    if (Part != 2)
        return 0;

    TempDate.Year = Number;

    if (!isDateValid(TempDate))
        return 0;

    Date->Day = TempDate.Day;
    Date->Month = TempDate.Month;
    Date->Year = TempDate.Year;

    return 1;
}
