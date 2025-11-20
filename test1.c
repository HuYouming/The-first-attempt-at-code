#include <stdio.h>
#include <string.h>
int main()
{
    char command[100];
    char* choose[] = {"Dian", "Quit"};

    while(1)
    {
        printf("Please input command:");
        scanf("%s",command);

        if(!strcmp(command, choose[0]))
        {
           printf("2002\n");
        }
        else if(!strcmp(command, choose[1]))
       {
           break;
       }
        else
       {
           printf("Error\n");
       }
    }

    return 0;
}