#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int chave;

}Registro;

typedef struct Nodo
{
    Registro reg;
    struct Nodo *pEsquerdo;
    struct Nodo *pDireito;
}Nodo;

Nodo *criaNodo(void);
int inserir(Nodo **ppRaiz, int num);
void listArvore (Nodo *pRaiz);
int remover(Nodo **ppRaiz, int numRemover);
Nodo *procuraNodoMenor(Nodo *atual);
void freeArvore (Nodo *pRaiz);

//Balanceamento
int balanceamento(Nodo **ppRaiz);
int balancaEsquerda (Nodo **ppRaiz);
int balancaDireita (Nodo **ppRaiz);
void RSE (Nodo **ppRaiz);
void RSD (Nodo **ppRaiz);
int FB (Nodo *pRaiz);
int altura (Nodo *pRaiz);
int ehArvoreAVL(Nodo *pRaiz);


int main ()
{
    int op = 0, numero = 0, nRemover = 0;
    Nodo *pRaiz = NULL;

    do
    {
        printf("\n1.  Inserir nodo na arvore\n");
        printf("2.  Listar a arvore\n");
        printf("3.  Retirar nodo da arvore\n");
        printf("4.  Verificar se a arvore e AVL\n");
        printf("5.  Sair\n");

        scanf("%d", &op);
        getchar();

        switch (op)
        {
        case 1:
            printf("\nDigite o numero que quer colocar na arvore: ");
            scanf("%d", &numero);
            getchar();
            inserir(&pRaiz, numero);
            break;
        
        case 2:
            printf("\nNodos da lista: ");
            listArvore(pRaiz);
            printf("\n");
            break;

        case 3:
            printf("\nDigite o numero a ser removido da arvore: ");
            scanf("%d", &nRemover);
            getchar();

            remover(&pRaiz, nRemover);
            break;

        case 4:
            if (ehArvoreAVL(pRaiz))
            {
                printf("\nEh uma arvore AVL\n");
            }
            else
            {
                printf("\nNao eh uma arvore AVL\n");
            }
            break;

        default:
            break;
        }
    } while (op != 5);

    freeArvore(pRaiz);    

    return 0 ;
}

Nodo *criaNodo(void)
{
    Nodo *newNodo = NULL;

    newNodo = (Nodo *)malloc(sizeof(Nodo));

    if (newNodo == NULL)
    {
        printf("Nao foi possivel alocar espaco para o nodo\n");
        exit(1);
    }

    newNodo->pDireito = NULL;
    newNodo->pEsquerdo = NULL;

    return newNodo;    
}

int inserir(Nodo **ppRaiz, int num)
{
    if (*ppRaiz == NULL)
    {
        *ppRaiz = criaNodo();
        (*ppRaiz)->reg.chave = num;
        return 1;
    }
    else if ((*ppRaiz)->reg.chave > num)
    {
        if (inserir(&(*ppRaiz)->pEsquerdo, num))
        {
            if (balanceamento(ppRaiz)) 
                return 0;
            else
                return 1;
        }
    }
    else if ((*ppRaiz)->reg.chave < num)
    {
        if(inserir(&(*ppRaiz)->pDireito, num))
        {
            if (balanceamento(ppRaiz))
                return 0;
            else
                return 1;
        }
        else
            return 0;
    }
    else
        return 0;
    
    return 0;
}

void listArvore (Nodo *pRaiz)
{
    if (pRaiz != NULL)
    {
        printf("%d(", pRaiz->reg.chave);
        listArvore(pRaiz->pEsquerdo);
        listArvore(pRaiz->pDireito);
        printf(")");
    }
}

int remover(Nodo **ppRaiz, int numRemover)
{
    int r;
    if (*ppRaiz == NULL)
    {
        printf("A arvore esta vazia!\n");
        return 0;
    }

    if (numRemover < (*ppRaiz)->reg.chave)
    {
        if ((r = remover(&(*ppRaiz)->pEsquerdo, numRemover)) == 1)
            balanceamento(ppRaiz);
    }

    if (numRemover > (*ppRaiz)->reg.chave)
    {
        if ((r = remover(&(*ppRaiz)->pDireito, numRemover)) == 1)
            balanceamento(ppRaiz);
    }

    if ((numRemover == (*ppRaiz)->reg.chave))
    {
        if((*ppRaiz)->pEsquerdo == NULL || (*ppRaiz)->pDireito == NULL)
        {
            Nodo *auxNodo = (*ppRaiz);
            if((*ppRaiz)->pEsquerdo != NULL)
                *ppRaiz = (*ppRaiz)->pEsquerdo;
            else
                *ppRaiz = (*ppRaiz)->pDireito;
            
            free(auxNodo);
        }
        else
        {
            Nodo *auxTemp = procuraNodoMenor((*ppRaiz)->pDireito);
            (*ppRaiz)->reg.chave = auxTemp->reg.chave;
            remover(&(*ppRaiz)->pDireito, (*ppRaiz)->reg.chave);
            balanceamento(ppRaiz);
        }

        return 1;
    }

    return r;
}

Nodo *procuraNodoMenor(Nodo *atual)
{
    Nodo *nodo, *nodoAux;

    nodo = atual;
    nodoAux = atual->pEsquerdo;
    while (nodoAux != NULL)
    {
        nodo = nodoAux;
        nodoAux = nodoAux->pEsquerdo;
    }
    
    return nodo;
}

void freeArvore (Nodo *pRaiz)
{
    if (pRaiz == NULL)
    {
        return;        
    }
    freeArvore(pRaiz->pEsquerdo);
    freeArvore(pRaiz->pDireito);
    free(pRaiz);
}

int balanceamento(Nodo **ppRaiz)
{
    int fb = FB(*ppRaiz);
    if (fb > 1)
        return balancaEsquerda(ppRaiz);
    else if (fb < -1)
        return balancaDireita(ppRaiz);
    else
        return 0;
}

int balancaEsquerda (Nodo **ppRaiz)
{
    int fbe = FB ( (*ppRaiz)->pEsquerdo);
    if (fbe >= 0)
    {
        RSD(ppRaiz);
        return 1;
    }
    else if (fbe < 0)
    {
        //Rotação dupla direita
        RSE(&((*ppRaiz)->pEsquerdo));
        RSD(ppRaiz);
        return 1;
    }

    return 0;
}

int balancaDireita (Nodo **ppRaiz)
{
    int fbd = FB ((*ppRaiz)->pDireito);
    if (fbd <= 0)
    {
        RSE(ppRaiz);
        return 1;
    }
    else if (fbd > 0)
    {
        //Rotação dupla esquerda
        RSD(&((*ppRaiz)->pDireito));
        RSE(ppRaiz);
        return 1;
    }

    return 0;
}

void RSE (Nodo **ppRaiz)
{
    Nodo *pAux;

    pAux = (*ppRaiz)->pDireito;
    (*ppRaiz)->pDireito = pAux->pEsquerdo;
    pAux->pEsquerdo = (*ppRaiz);
    (*ppRaiz) = pAux;
}

void RSD (Nodo **ppRaiz)
{
    Nodo *pAux;

    pAux = (*ppRaiz)->pEsquerdo;
    (*ppRaiz)->pEsquerdo = pAux->pDireito;
    pAux->pDireito = (*ppRaiz);
    (*ppRaiz) = pAux;
}

int FB (Nodo *pRaiz)
{
    if (pRaiz == NULL)
        return 0;
    
    return altura(pRaiz->pEsquerdo) - altura(pRaiz->pDireito);
}

int altura (Nodo *pRaiz)
{
    int iEsquerda, iDireita;

    if (pRaiz == NULL)
        return 0;
    
    iEsquerda = altura(pRaiz->pEsquerdo);
    iDireita = altura(pRaiz->pDireito);

    if (iEsquerda > iDireita)
        return iEsquerda + 1;
    else
        return iDireita + 1;
}

int ehArvoreAVL(Nodo *pRaiz)
{
    int fb;

    if (pRaiz == NULL)
        return 1;
    
    if (!ehArvoreAVL(pRaiz->pEsquerdo))
        return 0;
    if (!ehArvoreAVL(pRaiz->pDireito))
        return 0;
    
    fb = FB(pRaiz);

    if ((fb > 1) || (fb < -1))
        return 0;
    else
        return 1;   
}