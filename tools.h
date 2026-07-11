#ifndef TOOLS_H
#define TOOLS_H

void clearScreen(void);
void clearBuffer(void);
void waitForEnter(void);
int askYesOrNo(char *Question);
void printLine(char sign, int count);
int getText(const char *prompt, int maxLength, int allowEmpty, char **target);
int getNumber(char *Prompt, int *Number, int From, int To);
#endif
