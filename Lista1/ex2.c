#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readString(void);
char *insert(char *list);
char *pullOut(char *list);
void showList(char *list);

int main ()
{
    char *list = NULL;
    int option;
    
    do
    {
        printf("1.  Inserir\n2.  Remover\n3.  Mostrar nomes\n4.  Sair\n\nEscolha: ");
        scanf("%d", &option);
        getchar();

        switch (option)
        {
            case 1:
                list = insert(list);
                break;
            
            case 2:
                list = pullOut(list);
                break;
            
            case 3:
                showList(list);
                break;
            
            case 4:
                break;
        }
    } while (option != 4);
    
    free(list);

    return 0;
}

char *readString(void)
{
    char *newName = NULL;

    newName = (char*)malloc(20 * sizeof(char));
    printf("Digite um nome: ");
    scanf("%[^\n]s", newName);
    getchar();

    return newName;
}

char *insert(char *list)
{
    char *newName = NULL;
    int nameSize = 0, listSize = 0;

    newName = readString();

    nameSize = strlen(newName) + 1;  // \0

    if (!list)
    {
        list = (char *)malloc((nameSize + 1) * sizeof(char)); // \;
        strcpy(list, newName);
        strcat(list, ";");
    }
    else
    {
        listSize = strlen(list);
        list = (char *)realloc(list, (listSize + nameSize + 1) * sizeof(char));
        strcat(list, newName);
        strcat(list, ";");
    }

    printf("-------------------------------------------------------------\n");
    printf("\n");

    free(newName);

    return list;
}

char *pullOut (char *list)
{
    if (!list) return list;
    
    int listSize = strlen(list), auxSize = 0, nameSize = 0, newSize = 0;
    int i, j;
    char *listAux = NULL, *pullOutName = NULL, name[30];

    pullOutName = readString();

    for (i = 0; i < listSize; i++)
    {
        j = 0;

        while (list[i] != ';')
        {
            name[j++] = list[i++];
        }
        name[j] = '\0';

        nameSize = strlen(name) + 1;

        if (strcmp(pullOutName, name) != 0)
        {
            if (listAux == NULL)
            {
                newSize = nameSize + 1;
                listAux = (char *)malloc(newSize * sizeof(char));
                strcpy(listAux, name);
                strcat(listAux, ";");
            }
            else
            {
                newSize = auxSize + nameSize + 1;
                listAux = (char *)realloc(listAux, (auxSize + nameSize) * sizeof(char));
                strcat(listAux, name);
                strcat(listAux, ";");
            }
        }
        auxSize = newSize;
    }
    free(list);
    free(pullOutName);

    return listAux;
}

void showList (char *list)
{
    //printf("\n");
    while (*list)
    {
        if (*list != ';')
        {
            printf("%c", *list++);
        }
        else
        {
            printf("\n");
            list++;
        }
    }

    printf("-------------------------------------------------------------\n");
    printf("\n");
}