#include <stdio.h>
#include <stdlib.h>

/**********************************************************
 *
 **********************************************************/
void clearScreen()
{
//   system("clear");
   system("CLS");
}

/**********************************************************
 *
 **********************************************************/
void clearBuffer()
{
   char Dummy;

   do
   {
      scanf("%c", &Dummy);
   } while (Dummy != '\n');
}

/**********************************************************
 *
 **********************************************************/
void waitForEnter()
{
   printf("\nBitte Eingabetaste druecken ...");
   clearBuffer();
}

/**********************************************************
 *
 **********************************************************/
int askYesOrNo(char *Question)
{
   char Input;

   do
   {
      printf("%s", Question);
      scanf("%c", &Input);
      if (Input != '\n')
         clearBuffer();
   } while ((Input != 'j') && (Input != 'J') && (Input != 'n') && (Input != 'N'));
   return ((Input == 'j') || (Input == 'J'));
}

/**********************************************************
 *
 **********************************************************/

void printLine(char sign, int count)
{
	int i;
	for(i=0; i<= count; i++)
	{
		printf("%c", sign);
	}
	printf ("\n");
}
