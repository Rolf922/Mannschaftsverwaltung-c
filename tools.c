#include <stdio.h>
#include <stdlib.h>

/**********************************************************
 *
 **********************************************************/
void clearScreen()
{
//   system("clear"); // Linux / Mac
   system("CLS");   // Windows
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
