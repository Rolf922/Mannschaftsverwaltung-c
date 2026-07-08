#ifndef DATETIME_H
#define DATETIME_H

#include "datastructure.h"

int isLeapYear(int Year);
int isDateValid(sDate Date);
int getDateFromString(char *Input, sDate *Date);

#endif
