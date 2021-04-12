#include <stdio.h>
#include <stdlib.h>

int size = 0;

struct Person
{
    char name[10];
    int age;
    int height;
};

struct Person *insert(struct Person *p);
void list(struct Person *p);

int main ()
{
    struct Person *p = NULL;
    int op;

    do
    {
        printf("--------------------------\n1.  Inserir\n");
        printf("2.  Listar e sair\n--------------------------\n");
        scanf("%d", &op);
        getchar();

        switch (op)
        {
            case 1:
                p = insert(p);
                break;
        
            case 2:
                list(p);
            default:
                break;
        }

    } while (op != 2);

    free(p);
}

struct Person *insert(struct Person *p)
{
    if(p == NULL)
    {
        p = (struct Person *)malloc(sizeof(struct Person));

        printf("Digite um nome: ");
        scanf("%[^\n]s", p[size].name);
        getchar();

        printf("Idade: ");
        scanf("%d", &p[size].age);

        printf("Altura: ");
        scanf("%d", &p[size].height);
        
        size++;
    }
    else
    {
        p = (struct Person *)realloc(p ,((size + 1) * sizeof(struct Person)));

        printf("Digite um nome: ");
        scanf("%[^\n]s", p[size].name);
        getchar();

        printf("Idade: ");
        scanf("%d", &p[size].age);

        printf("Altura: ");
        scanf("%d", &p[size].height);

        size++;
    }
    return p;
}

void list(struct Person *p)
{
    for(int i = 0; i < size; i++)
    {
        printf("--------------------------\n%s\n", p[i].name);
        printf("%d\n", p[i].age);
        printf("%d\n--------------------------", p[i].height);
        printf("\n\n");
    }
}