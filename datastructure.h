#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#define MAXPLAYER 23
#define MAXTEAMS 10

typedef struct
{
	int Day;
	int Month;
	int Year;
} sDate;

typedef struct
{
	char *playername;
	sDate *birthday;
	int shirtnumber;
	int goals;
} sPlayer;

typedef struct
{
	char *teamname;
	char *coachname;
	int playercount;
	sPlayer players[MAXPLAYER];
} sTeam;

extern int Teamcounter;
extern sTeam Team[MAXTEAMS];

#endif
