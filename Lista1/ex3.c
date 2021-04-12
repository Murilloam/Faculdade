#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *insert(void *pBuffer);
void *fRemove(void *pBuffer);
void search(void *pBuffer);
void list(void *pBuffer);

int main ()
{
    void *pBuffer = NULL;
    int op = 0;

    pBuffer = malloc(sizeof(int));
    *(int*)pBuffer = 0;

    do
    {
        printf("1.  Inserir \n");
        printf("2.  Listar\n");
        printf("3.  Buscar\n");
        printf("4.  Remover\n");
        printf("5.  Sair\n");

        scanf("%d", &op);
        getchar();
        
        switch (op)
        {
            case 1:
                pBuffer = insert(pBuffer);
                break;

            case 2:
                list(pBuffer);
                break;
            
            case 3:
                search(pBuffer);
                break;
            
            case 4:
                pBuffer = fRemove(pBuffer);
        }

    } while (op != 5);
    
    free(pBuffer);
}

void *insert(void *pBuffer)
{
   pBuffer = realloc(pBuffer, sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int))  * ((*(int*)pBuffer) + 1)));


   printf("\nDigite o nome: ");
   scanf("%s", (char *)(pBuffer + sizeof(int) + ((10 * sizeof(char)) + (2 * sizeof(int))) * (*(int *)pBuffer)));
   getchar();

   printf("Idade: ");
   scanf("%d", (int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + ((10 * sizeof(char)) + (2 * sizeof(int))) * (*(int *)pBuffer)));

   printf("Numero de telefone: ");
   scanf("%d", (int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (sizeof(int)) + ((10 * sizeof(char)) + (2 * sizeof(int))) * (*(int *)pBuffer)));

   printf("------------------------------------------------\n\n");

   *(int *)pBuffer = *(int *)pBuffer + 1;

    return pBuffer;
}

void *fRemove(void *pBuffer)
{
    char name[10];
    int i = 0;

    if(*(int *)pBuffer == 0)
    {
        printf("Nao ha nomes na agenda.\n\n");
        return pBuffer;
    }
    else
    {
        printf("Nome a ser removido: ");
        scanf("%s", name);
        getchar();

        for(i = 0; i < *(int *)pBuffer; i++)
        {
            if (strcmp(name, (char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)) == 0)
            {
                strcpy((char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i), (char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int *)(pBuffer) - 1)));
                *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)) = *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int *)(pBuffer) - 1)));
                *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)) = *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * (*(int *)(pBuffer) - 1)));
                *(int *)pBuffer = *(int *)pBuffer - 1;
                pBuffer = realloc(pBuffer, sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int))  * ((*(int*)pBuffer))));

                return pBuffer;
            }
        }
    }
    printf("O nome digitado nao consta com nenhum da lista.\n");
    return pBuffer;
}

void search(void *pBuffer)
{
    char name[10];
    int i = 0;

    if (*(int *)pBuffer == 0)
    {
        printf("Nao ha nomes a serem buscados.\n\n");
    }
    else
    {
        printf("Nome a ser buscado: ");
        scanf("%s", name);
        getchar();
        
        for(i = 0; i < *(int *)pBuffer; i++)
        {
            if (strcmp(name, (char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)) == 0)
            {
                printf("------------------------------------------------\n");
                printf("Nome: %s\n", (char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i));
                printf("Idade: %d\n", *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)));
                printf("Telefone: %d\n", *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)));
                printf("------------------------------------------------\n");
            }
        }
    }

    // return pBuffer;
}

void list(void *pBuffer)
{
    printf("------------------------------------------------\n");
    for(int i = 0; i < *(int *)pBuffer; i++)
    {
        printf("Nome: %s\n", (char *)pBuffer + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i));
        printf("Idade: %d\n", *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)));
        printf("Telefone: %d\n", *(int *)(pBuffer + sizeof(int) + (10 * sizeof(char)) + sizeof(int) + (((10 * sizeof(char)) + sizeof(int) + sizeof(int)) * i)));
        printf("\n");
    }
    printf("------------------------------------------------\n");
}