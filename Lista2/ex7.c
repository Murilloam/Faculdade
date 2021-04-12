#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char name[10];
    int age;
    int tel;
}Person;
Person list[10];

void insert(void *pBuffer);
void toList(void *pBuffer);
void search(void *pBuffer);
void toRemove(void *pBuffer);


int main ()
{
    void *pBuffer = NULL;

    pBuffer = malloc(sizeof(int) + (sizeof(int)) + (sizeof(int)) + (10 * sizeof(char))); //seletor switch, index, i 
    *(int *)(pBuffer + sizeof(int)) = 0;


    do
    {
        printf("1.  Inserir \n");
        printf("2.  Listar\n");
        printf("3.  Buscar\n");
        printf("4.  Remover\n");
        printf("5.  Sair\n");

        scanf("%d", (int *)pBuffer);
        getchar();
        
        switch (*(int *)(pBuffer))
        {
            case 1:
                insert(pBuffer);
                break;

            case 2:
                toList(pBuffer);
                break;
            
            case 3:
                search(pBuffer);
                break;
            
            case 4:
                toRemove(pBuffer);
        }

    } while (*(int *)pBuffer != 5);
    
    free(pBuffer);
    

    return 0;
}

void insert(void *pBuffer)
{    
    printf("\nDigite o nome: ");
    scanf("%[^\n]s", list[*(int *)(pBuffer + sizeof(int))].name);

    printf("Idade: ");
    scanf("%d", &list[*(int *)(pBuffer + sizeof(int))].age);

    printf("Numero de telefone: ");
    scanf("%d", &list[*(int *)(pBuffer + sizeof(int))].tel);
    

    printf("------------------------------------------------\n\n");

    *(int *)(pBuffer + sizeof(int)) = *(int *)(pBuffer + sizeof(int)) + 1;

}

void toList(void *pBuffer)
{
    if(*(int *)(pBuffer + sizeof(int)) == 0)
    {
        printf("------------------------------------------------\nNao ha nada na lista a ser mostrado.\n------------------------------------------------\n");
    }
    else
    {
        printf("------------------------------------------------\n");
        for(*(int *)(pBuffer + sizeof(int) + sizeof(int)) = 0; *(int *)(pBuffer + sizeof(int) + sizeof(int)) < *(int *)(pBuffer + sizeof(int)); *(int *)(pBuffer + sizeof(int) + sizeof(int)) = *(int *)(pBuffer + sizeof(int) + sizeof(int)) + 1)
        {
            if (list[*(int *)(pBuffer + sizeof(int) + sizeof(int))].name[0] != '\0')
            {
                printf("Nome: %s\n", list[*(int *)(pBuffer + sizeof(int) + sizeof(int))].name);
                printf("Idade: %d\n", list[*(int *)(pBuffer + sizeof(int) + sizeof(int))].age);
                printf("Numero de telefone: %d\n", list[*(int *)(pBuffer + sizeof(int) + sizeof(int))].tel);
            }
            printf("------------------------------------------------\n");
        }
    }    
}

void search(void *pBuffer)
{
    if (*(int *)(pBuffer + sizeof(int)) == 0)
    {
        printf("------------------------------------------------\nNao ha nada na lista a ser buscado.\n------------------------------------------------\n");
    }
    else
    {
        printf("Nome a ser buscado: ");
        scanf("%[^\n]s", (char *)pBuffer + sizeof(int) + sizeof(int) + sizeof(int));

        
        for(*(int *)(pBuffer + sizeof(int) + sizeof(int)) = 0; *(int *)(pBuffer + sizeof(int) + sizeof(int)) < *(int *)(pBuffer + sizeof(int)); *(int *)(pBuffer + sizeof(int) + sizeof(int)) = *(int *)(pBuffer + sizeof(int) + sizeof(int)) + 1)
        {
            if(strcmp((char *)pBuffer + sizeof(int) + sizeof(int) + sizeof(int), list[*(int *)(pBuffer + sizeof(int) + sizeof(int))].name) == 0)
            {
                printf("------------------------------------------------\n");
                printf("Nome: %s\n", list[*(int *)(pBuffer + sizeof(int) + sizeof(int))].name);
                printf("Idade: %d\n", list[*(int *)(pBuffer + sizeof(int) + sizeof(int))].age);
                printf("Numero de telefone: %d\n", list[*(int *)(pBuffer + sizeof(int) + sizeof(int))].tel);
                printf("------------------------------------------------\n");
            }
        }

    }

}
    
void toRemove(void *pBuffer)
{
     if (*(int *)(pBuffer + sizeof(int)) == 0)
    {
        printf("------------------------------------------------\nNao ha nada na lista a ser removido.\n------------------------------------------------\n");
    }
    else
    {
        printf("Nome a ser removido: ");
        scanf("%[^\n]s", (char *)pBuffer + sizeof(int) + sizeof(int) + sizeof(int));

        for(*(int *)(pBuffer + sizeof(int) + sizeof(int)) = 0; *(int *)(pBuffer + sizeof(int) + sizeof(int)) < *(int *)(pBuffer + sizeof(int)); *(int *)(pBuffer + sizeof(int) + sizeof(int)) = *(int *)(pBuffer + sizeof(int) + sizeof(int)) + 1)
        {
            if(strcmp((char *)pBuffer + sizeof(int) + sizeof(int) + sizeof(int), list[*(int *)(pBuffer + sizeof(int) + sizeof(int))].name) == 0)
            {
                strcpy(list[*(int *)(pBuffer + sizeof(int) + sizeof(int))].name, (list[*(int *)(pBuffer + sizeof(int)) - 1].name));
                list[*(int *)(pBuffer + sizeof(int) + sizeof(int))].age = (list[*(int *)(pBuffer + sizeof(int)) - 1].age);
                list[*(int *)(pBuffer + sizeof(int) + sizeof(int))].tel = (list[*(int *)(pBuffer + sizeof(int)) - 1].tel);

                list[*(int *)(pBuffer + sizeof(int)) - 1].name[0] = '\0';
                list[*(int *)(pBuffer + sizeof(int)) - 1].age = -1;
                list[*(int *)(pBuffer + sizeof(int)) - 1].tel = -1;

                *(int *)(pBuffer + sizeof(int)) = *(int *)(pBuffer + sizeof(int)) - 1;
            }
        }
    }
}


