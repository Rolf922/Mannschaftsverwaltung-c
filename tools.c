#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**********************************************************
 *
 **********************************************************/
void clearScreen()
{
//   system("clear");
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

/****************************************************************************************
*Funktion zur Zahleneingabe mit dynamischer Speicherwervaltung
 * Liest eine Zahl ein und prueft, ob sie im erlaubten
 * Bereich zwischen From und To liegt.
****************************************************************************************/

int getNumber(char *Prompt, int *Number, int From, int To)
{
    int Input;
    int ScanResult;
    int ValidInput = 0;

    if ((Prompt == NULL) || (Number == NULL) || (From > To))
    {
        return 0;
    }

    do
    {
        printf("%s", Prompt);

        ScanResult = scanf("%d", &Input);
        clearBuffer();

        if (ScanResult == 1)
        {

            if ((Input >= From) && (Input <= To))
            {
                ValidInput = 1;
            }
            else
            {
                printf("Bitte eine Zahl zwischen %d und %d eingeben!\n", From, To);
            }
        }
        else
        {
            clearBuffer();
            printf("Ungueltige Eingabe! Bitte eine Zahl eingeben.\n");
        }

    } while (!ValidInput);

    *Number = Input;

    return 1;
}

/*****************************************************************************************
*Funktion zur Texteingabe mit dynamischer Speicherverwaltung
*****************************************************************************************/

int getText(const char *prompt, int maxLength, int allowEmpty, char **target) {
    char format[20];
    int validInput, len;

    // Check whether the user provided the pointer of pointer (target)
    if (target == NULL) {
        fprintf(stderr, "Adresse zur Speicherung nicht vorhanden.\n");
        return 0; // Error
    }

    // Allocate memory for a temporary input buffer
    char *inputBuffer = (char *)malloc(maxLength + 1); // Memory allocation = max char (1 byte) length + 1 for null terminator
    if (inputBuffer == NULL) {
        fprintf(stderr, "Speicher-Reservierung nicht moeglich\n");
        return 0; // Error
    }

    if (inputBuffer) { // When inputBuffer successfully allocated
        sprintf(format, "%%%i[^\n]", maxLength); // Set formatting for text input, limited by maxLength, will ignore \n

        while (1) {
            printf("%s", prompt); // Show the prompt

            // Use scanf to read the input
            validInput = scanf(format, inputBuffer); // Read the input

            if (validInput != 1) {
                inputBuffer[0] = '\0'; // Set inputBuffer to empty string if no valid input
            }
            clearBuffer();

            len = strlen(inputBuffer); // Count the length of input

            if (validInput == 1 && (allowEmpty || len > 0)) {
                // Allocate memory for the target string based on the length of the input
                *target = (char *)malloc(len + 1); // +1 for null terminator
                if (*target == NULL) {
                    fprintf(stderr, "Memory allocation for target failed.\n");
                    free(inputBuffer); // Release memory
                    return 0; // Error
                }

                strcpy(*target, inputBuffer); // Copy input to target
                free(inputBuffer); // Release the temporary input buffer
                return 1; // Success
            }

            if (allowEmpty) {
                free(inputBuffer);
                return 1; // Success when empty input is allowed
            }

            if (!allowEmpty && len == 0) {
                fprintf(stderr, "\n Eingabe darf nicht leer sein!\n");
            }
        }
    }
    return 0; // Fallback error
}
