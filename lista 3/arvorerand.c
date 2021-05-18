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
int inserir(Nodo **ppRaiz, Registro reg);
void registrarChave (Registro *reg);
void listArvore (Nodo *pRaiz);
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
    int i = 0, numeroNodos = 0;
    Registro reg;
    Nodo *pRaiz = NULL;

    printf("Numero de nodos que quer: ");
    scanf("%d", &numeroNodos);
    getchar();

    printf("\nOs numeros gerados aleatoriamente foram: ");
    for(i = 0; i < numeroNodos; i++)
    {
        registrarChave(&reg);
        inserir(&pRaiz, reg);
    }

    printf("\n------------------------------\n");

    printf("A arvore: ");

    listArvore(pRaiz);

    printf("\n------------------------------\n");
    
    if (ehArvoreAVL(pRaiz) == 1)
    {
        printf("E uma arvore AVL!\n");
    }
    else{
        printf("Nao e uma arvore AVL!\n");
    }

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

void registrarChave (Registro *reg) {

    int random;

    random = rand()%1000;
    printf("%d, ", random);
    reg->chave = random;
}

int inserir(Nodo **ppRaiz, Registro oReg)
{
    if (*ppRaiz == NULL)
    {
        *ppRaiz = criaNodo();
        (*ppRaiz)->reg = oReg;
        return 1;
    }
    else if ((*ppRaiz)->reg.chave > oReg.chave)
    {
        if (inserir(&(*ppRaiz)->pEsquerdo, oReg))
        {
            if (balanceamento(ppRaiz)) 
                return 0;
            else
                return 1;
        }
    }
    else if ((*ppRaiz)->reg.chave < oReg.chave)
    {
        if(inserir(&(*ppRaiz)->pDireito, oReg))
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
    if (fbe > 0)
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
    if (fbd < 0)
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