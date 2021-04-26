#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct element
{
    char name[10];
    int age, tel;


    struct element *next;
    struct element *prev;

}element;

typedef struct head
{
    element *start;
    element *final;
}head;

head *createList(void);
void freeList(head *list);
void insert(head *list);
void removeElement(head *list, void *pBuffer);
void search(head *list, void *pBuffer);
void showList(head *list);
//----------------------------------------------------------------------------//
void orderedMenu(head *list, void *pBuffer);
void orderedGrowingAge(head *list, void *pBuffer);
void orderedDecreasingAge(head *list, void *pBuffer);
void orderedList(head *list, void *pBuffer);
void PUSH(head *list, element *linkedList, void *pBuffer);
void POP(element *aux);


int main()
{
    void *pBuffer = NULL;

    pBuffer = malloc((sizeof(int)) +(10 * sizeof(char)) + (sizeof(int))+ (sizeof(int)) + (sizeof(int))); 
    //int do primeiro switch, string para pegar o nome a ser removido e a ser buscado, int do segundo switch, menor numero (para ordenar), maior numero

    head *list = NULL;

    list = createList();

    do
    {
        printf("1.  Inserir \n");
        printf("2.  Listar\n");
        printf("3.  Buscar\n");
        printf("4.  Remover\n");
        printf("5.  Ordenar lista\n");
        printf("6.  Sair\n");

        scanf("%d", (int *)pBuffer);
        getchar();
        
        switch (*(int *)pBuffer)
        {
            case 1:
                insert(list);
                break;

            case 2:
                showList(list);
                break;
            
            case 3:
                search(list, pBuffer);
                break;
            
            case 4:
                removeElement(list, pBuffer);
                break;

            case 5:
                orderedMenu(list, pBuffer);
                break;
            
            case 6:
                freeList(list);
                free(pBuffer);
                return 0;
        }

    } while (*(int *)pBuffer != 6);

    return 0;
}

head *createList(void)
{
    head *list;

    list = (head *)malloc(sizeof(head));

    list->start = NULL;
    list->final = NULL;

    return list;
}

void freeList(head *list)
{
    element *aux, *p;

    p = list->start;

    while(p != NULL)
    {

        aux = p;
        p = p->next;

        free(aux);
    }
    
    free(list);

}

void insert(head *list)
{
    element *newKnot = NULL;
    newKnot = (element *)malloc(sizeof(element));
    newKnot->next = NULL;
    newKnot->prev = NULL;

    printf("----------------------------\nDigite o nome: ");
    scanf("%s", newKnot->name);
    getchar();

    printf("Idade: ");
    scanf("%d", &newKnot->age);

    printf("Telefone: ");
    scanf("%d", &newKnot->tel);
    printf("----------------------------\n");

    if (list->start == NULL)
    {
        list->start = newKnot;
    }
    else
    {
        newKnot->prev = list->final;
        list->final->next = newKnot;
    }

    list->final = newKnot;
}

void removeElement  (head *list, void *pBuffer)
{
    if(list->start == NULL)
    {
        printf("Nao ha nada na lista para ser removido!\n");
    }

    else
    {
        element *aux = NULL;
        aux = list->start;

        printf("Pessoa a ser removida: ");
        scanf("%s", (char *)pBuffer + (sizeof(int)));
        getchar();

        while (aux != NULL)
        {
            if(strcmp(aux->name, (char *)pBuffer + (sizeof(int))) == 0)
            {
                if(aux->prev == NULL)       
                {
                    if (aux->next == NULL)  //Remover quando só tem um elemento
                    {
                        list->start = NULL;
                        list->final = NULL;

                        free(aux);

                        return;
                    }

                    else    //Remover quando o nodo for o primeiro da lista
                    {
                        aux->next->prev = NULL;
                        list->start = aux->next;

                        free(aux);

                        return;
                    }
                }
                    else if(aux->next != NULL) // remover quando está no meio da lista
                    {
                        aux->prev->next = aux->next;
                        aux->next->prev = aux->prev;

                        free (aux);

                        return;
                    }
                
                else    //Remove quando o nodo está no final da lista
                {
                    aux->prev->next = NULL;
                    list->final = aux->prev;

                    free (aux);

                    return;
                }
            }

            aux = aux->next;
        }
    }
}

void search(head *list, void *pBuffer)
{
    if(list->start == NULL)
    {
        printf("Lista vazia!\n");
    }
    else
    {
        element *aux = NULL;
        aux = list->start;

        printf("Digite o nome a ser procurado: ");
        scanf("%s", (char *)pBuffer + (sizeof(int)));
        getchar();

        while (aux != NULL)
        {
            if(strcmp(aux->name, (char *)pBuffer + (sizeof(int))) == 0)
            {
                printf("----------------------------\n");
                printf("Nome: %s\n", aux->name);
                printf("Idade: %d\n", aux->age);
                printf("Telefone: %d\n", aux->tel);
                printf("----------------------------\n");
            }

            aux = aux->next;
        }  
    }
}

void showList(head *list)
{
    if (list == NULL)
    {
        printf("----------------------------\nLista vazia!\n");
    }
    else
    {
        element *aux = NULL;
        aux = list->start;

        while(aux != NULL)
        {
            printf("----------------------------\nNome: %s\n", aux->name);
            printf("Idade: %d\n", aux->age);
            printf("Telefone: %d\n", aux->tel);
            printf("----------------------------\n");

            aux = aux->next;
        }
    }
    
}

void orderedMenu(head *list, void *pBuffer)
{
    if(list->start == NULL)
    {
        printf("A lista esta vazia, nao ha nada a ser ordenado!\n");
        printf("----------------------------\n");
        return;
    }
    printf("----------------------------\n");
    printf("1.  Ordenar a idade em ordem crescente\n");
    printf("2.  Ordenar a idade em ordem decrescente\n");
    printf("3.  Voltar\n");
    scanf("%d", (int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char))));
    getchar();

    switch ( *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char))))
    {
    case 1:
        orderedGrowingAge(list, pBuffer);
        break;

    case 2:
        orderedDecreasingAge(list, pBuffer);
        break;

    case 3:
        return;
    
    default:
        break;
    }

    return;
}

void orderedGrowingAge(head *list, void *pBuffer)
{
    head *toOrderedList = NULL;
    toOrderedList = createList();

    element *auxi, *auxj, *auxk;

    //menor numero
    *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int))) = -1;

    for(auxi = list->start; auxi != NULL; auxi = auxi->next)
    {
        //maior numero
        *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int)) + (sizeof(int))) = 1000000000;

        for (auxj = list->start; auxj != NULL; auxj = auxj->next)
        {
            if (auxj->age > *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int))) && auxj->age < *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int)) + (sizeof(int))))
            {
                *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int)) + (sizeof(int))) = auxj->age;
            }
        }

        *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int))) = *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int)) + (sizeof(int)));

        for (auxk = list->start; auxk != NULL; auxk = auxk->next)
        {   
            if(auxk->age == *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int))))
            PUSH(toOrderedList, auxk, pBuffer);
        }
        
    }
    orderedList(toOrderedList, pBuffer);

}

void orderedDecreasingAge(head *list, void *pBuffer)
{
    head *toOrderedList = NULL;
    toOrderedList = createList();

    element *auxi, *auxj, *auxk;

    //maior numero
    *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int)) + (sizeof(int))) = 1000000000;


    for(auxi = list->start; auxi != NULL; auxi = auxi->next)
    {
        //menor numero
        *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int))) = -1;

        for (auxj = list->start; auxj != NULL; auxj = auxj->next)
        {
            if (auxj->age < *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int)) + (sizeof(int))) && auxj->age > *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int))))
            //se a idade for menor do que o maior numero E a idade for maior que o menor numero então
            {
                //O menor numero vai receber o maior numero que tá na lista
                *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int))) = auxj->age;
            }
            
        }
        //maior numero vai receber o numero que foi encontrado como o maior
        *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int)) + (sizeof(int))) = *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int)));
    

        for (auxk = list->start; auxk != NULL; auxk = auxk->next)
        {
            if(auxk->age == *(int *)(pBuffer + (sizeof(int)) + (10 * sizeof(char)) + (sizeof(int))))
            PUSH(toOrderedList, auxk, pBuffer);
        }
    }
        orderedList(toOrderedList, pBuffer);
}

void orderedList(head *list, void *pBuffer)
{
    if(list->start == NULL)
        printf("Lista vazia!\n");
    
    else
    {
        element *aux = NULL;
        element *p = NULL;
        aux = list->start;

        while (aux != NULL)
        {
            p = aux->next;
            POP(aux);
            aux = p;
        }
        
        free(list);
    }
}

void PUSH(head *list, element *linkedList, void *pBuffer)
{
    element *pLL = NULL; // LL = linked list
    pLL = (element *)malloc(sizeof(element));
    pLL->next = NULL;
    pLL->prev = NULL;

    strcpy(pLL->name, linkedList->name);
    pLL->age = linkedList->age;
    pLL->tel = linkedList->tel;

    if(list->start == NULL)
    {
        list->start = pLL;
    }
    else
    {
        pLL->prev = list->final;
        list->final->next = pLL;
    }
    list->final = pLL;

}


void POP(element *aux)
{
    printf("----------------------------\n");
    printf("Nome: %s\n", aux->name);
    printf("Idade: %d\n", aux->age);
    printf("Telefone: %d\n", aux->tel);
    printf("----------------------------\n");
    free(aux);
}