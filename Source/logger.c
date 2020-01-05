#include "logger.h"

void debugInfoVector2(Vector2 vec, char *additionalText)
{
    char *filename = "debug.log";
    FILE *fp = fopen(filename, "a");
    fprintf(fp, "DEBUG [Vector2] : %s <%f, %f>\n", additionalText, vec.x, vec.y);
    fclose(fp);
}

void debugInfoInt(int number, char *additionalText)
{
    char *filename = "debug.log";
    FILE *fp = fopen(filename, "a");
    fprintf(fp, "DEBUG [int] : %s - %d\n", additionalText, number);
    fclose(fp);
}

void debugInfoText(char *additionalText)
{
    char *filename = "debug.log";
    FILE *fp = fopen(filename, "a");
    fprintf(fp, "DEBUG [Text] : %s\n", additionalText);
    fclose(fp);
}

void debugInfoAdress(void *adress, char *addText)
{
    char *filename = "debug.log";
    FILE *fp = fopen(filename, "a");
    fprintf(fp, "DEBUG [ADRESS] : %p - %s \n", adress, addText);
    fclose(fp);
}

void debugStart()
{
    char *filename = "debug.log";
    FILE *fp = fopen(filename, "a");
    fprintf(fp, "------------------------ New session ------------------------\n");
    fclose(fp);
}