#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#define MAXPLAYER 23

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
	char *trainername;
	int playercount;
	sPlayer players[MAXPLAYER];

	struct sTeam *next;
	struct sTeam *prev;
} sTeam;

extern int Teamcounter;
extern sTeam *FirstTeam;
extern sTeam *LastTeam;

#endif
