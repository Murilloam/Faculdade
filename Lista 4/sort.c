#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

void insertionSort (int *vector, int vectorSize);
void selectionSort (int *vector, int vectorSize);
void quickSort (int *vector, int left, int right);
void mergeSort (int *vector, int start, int end);
void merge (int *vector, int mid, int start, int end);
int verificaOrdem (int *vector, int vectorSize);
int *createVector (int vectorSize);
void listVector (int *vector, int vectorSize);
int freeVector (int *vector);
float time_diff(struct timeval *start, struct timeval *end);

int main ()
{
    int vectorSize = 0, *vector, selector = 0;
    struct timeval begin, end;
    srand(time(NULL));

    do
    {
        printf("--------------------- Menu ---------------------\n");

        printf("1.  Insertion sort\n");
        printf("2.  Selection sort\n");
        printf("3.  Quick sort\n");
        printf("4.  Merge sort\n");
        printf("5.  Verificar ordenacao\n");
        printf("6.  Sair\n");

        scanf("%d", &selector);
        getchar();


        switch (selector)
        {
        case 1:
            //insertion sort
            printf("Tamanho do vector: ");
            scanf("%d", &vectorSize);
            getchar();
            
            vector = createVector(vectorSize);
            
            gettimeofday(&begin, NULL);
            insertionSort(vector, vectorSize);
            gettimeofday(&end, NULL);
            listVector(vector, vectorSize);

            printf("\nDemorou %f segundos para executar o insertion sort.\n", time_diff(&begin, &end));

            if(verificaOrdem(vector, vectorSize - 1))
            {
                printf("ta bom\n");
            }
            else
                printf("ta ruim\n");

            vectorSize = freeVector(vector);
            break;
        
        case 2: 
            //selection sort
            printf("Tamanho do vector: ");
            scanf("%d", &vectorSize);
            getchar();
            
            vector = createVector(vectorSize);

            gettimeofday(&begin, NULL);
            selectionSort(vector, vectorSize);
            gettimeofday(&end, NULL);
            listVector(vector, vectorSize);

            printf("\nDemorou %f segundos para executar o selection sort.\n", time_diff(&begin, &end));

            if(verificaOrdem(vector, vectorSize - 1))
            {
                printf("ta bom\n");
            }
            else
                printf("ta ruim\n");

            vectorSize = freeVector(vector);
            break;

        case 3: 
            //quick sort
           printf("Tamanho do vector: ");
            scanf("%d", &vectorSize);
            getchar();
            
            vector = createVector(vectorSize);
            gettimeofday(&begin, NULL);
            quickSort(vector, 0, vectorSize - 1);
            gettimeofday(&end, NULL);
            listVector(vector, vectorSize);

            printf("\nDemorou %f segundos para executar o quick sort.\n", time_diff(&begin, &end));

            if(verificaOrdem(vector, vectorSize - 1))
            {
                printf("ta bom\n");
            }
            else
                printf("ta ruim\n");

            vectorSize = freeVector(vector);
            break;

        case 4:
            //merge sort
            printf("Tamanho do vector: ");
            scanf("%d", &vectorSize);
            getchar();
            
            vector = createVector(vectorSize);
            gettimeofday(&begin, NULL);
            mergeSort(vector, 0, vectorSize - 1);
            gettimeofday(&end, NULL);
            listVector(vector, vectorSize);

            printf("\nDemorou %f segundos para executar o merge sort.\n", time_diff(&begin, &end));

            if(verificaOrdem(vector, vectorSize - 1))
            {
                printf("ta bom\n");
            }
            else
                printf("ta ruim\n");

            vectorSize = freeVector(vector);
            break;
        default:
            break;
        }

    } while (selector != 6);

    return 0;
}

void insertionSort (int *vector, int vectorSize)
{
    int i, j, aux;

    for(i = 1; i < vectorSize; i++)
    {
        aux = vector[i];
        for(j = i; (j > 0) && (aux < vector[j - 1]); j--)
        {
            vector[j] = vector[j - 1];
        }
        vector[j] = aux;
    }
}

void selectionSort (int *vector, int vectorSize)
{
    int min, temp, i, j, min_id = 0;

    for (i = 0; i < (vectorSize -1 ); i++) 
    {
        min = vector[i];

        for(j = i + 1; j < vectorSize; j++) 
        {
            if(vector[j] < min)
            {
                min = vector[j];
                min_id = j;
            }
        }

        temp = vector[i];
        vector[i] = vector[min_id];
        vector[min_id] = temp;
        min_id = i + 1;
    }
} 

void quickSort (int *vector, int left, int right)
{
    int i = left, j = right, aux, pivo;

    pivo = vector[left + (rand() % (right - left))];

    do
    {
        while(vector[i] < pivo)
        {
            i++;
        }

        while(pivo < vector[j])
        {
            j--;
        }

        if(i <= j)
        {
            aux = vector[i];
            vector[i] = vector[j];
            vector[j] = aux;
            i++;
            j--;
        }
    }while(i <= j);

    if(left < j)
    {
        quickSort(vector, left, j);
    }

    if(i < right)
    {
        quickSort(vector, i, right);
    }
}

void mergeSort(int *vector, int start, int end) {

    if (start < end) {

        int mid;

        mid = start + (end - start)/2;

        mergeSort(vector, start, mid);
        mergeSort(vector, mid +1, end);

        merge (vector, start, mid, end);
    }

}

void merge (int *vector, int start, int mid, int end) 
{
    
    int *temp, p1, p2, tam, i, j, k;
    int end1 = 0, end2 = 0;
    tam = end-start+1;
    p1 = start;
    p2 = mid +1;

    temp = (int *)malloc(tam * sizeof(int));
    if (temp != NULL) 
    {
        for(i = 0; i < tam; i++) 
        {
            if( (!end1) && (!end2) ) 
            {

                if (vector[p1] < vector[p2]) 
                {
                    temp[i] = vector[p1++];
                }
                else 
                {
                    temp[i] = vector[p2++];
                }

                if(p1 > mid) 
                {
                    end1=1;
                }
                if(p2>end) 
                {
                    end2=1;
                }
            }
            else 
            {
                if(!end1) 
                {
                    temp[i] = vector[p1++];
                }
                else 
                {
                    temp[i] = vector[p2++];
                }
            }
        }
        for(j = 0, k = start; j < tam; j++, k++) 
        {
            vector[k] = temp[j];
        }
    }

    free (temp);
}

int verificaOrdem (int *vector, int vectorSize) {

    int flag = 0, i;

    for (i = 0; i < vectorSize; i++) 
    {
        if(vector[i] > vector[i + 1]) 
        {
            flag++;
        }

    }
    if (flag == 0) 
    {
        return 1;
    }
    else 
    {
        return 0;
    }
}

int *createVector (int vectorSize)
{
    int *vector, i = 0;

    vector = malloc(vectorSize * sizeof(int));
    for(i = 0; i < vectorSize; i++)
    {
        vector[i] = rand ();
    }

    return vector;
}

void listVector (int *vector, int vectorSize)
{
    int i = 0;

    printf("Os numeros ordenados: ");
    for(i = 0; i < vectorSize; i++)
        {
            printf("%d, ", vector[i]);
        }
    printf("\n\n");
}

int freeVector (int *vector)
{
    free(vector);

    return 0;
}

float time_diff(struct timeval *start, struct timeval *end) {

    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}