#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include "datastructure.h"


void insertDListElement(sTeam *newTeam,
                        int (*compare)(sTeam *, sTeam *));

void removeDListElement(sTeam *team);

#endif // LIST_H_INCLUDED
