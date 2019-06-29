#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main( int argc, char *argv[])
{
    FILE *matrixFile;
    FILE *nameFile;
    FILE *outputFile;
    int temp;
    int stackTop = 0;
    int visited = 0;
    int size = atoi(argv[4]);
    int indegree[size];
    int stack[size];
    int sorted[size];
    bool matrix[size][size];
    char names[size][256];
    char name[256];
    // <exe> <matrixFile> <nameFile> <outFile> <matrixSize>

    matrixFile = fopen(argv[1], "r");
    nameFile = fopen(argv[2], "r");
    outputFile = fopen(argv[3], "w");
    if( matrixFile == NULL || nameFile == NULL)
    {
        printf("Could not open file.\n");
        return -1;
    }
    // matrix array
    for( int a = 0; a < size; a++)
    {
        for( int b = 0; b < size; b++)
        {
            fscanf( matrixFile, "%i", &temp);
            if( temp == 0)
            {
                matrix[a][b] = false;
            }
            else
            {
                matrix[a][b] = true;
            }
        }
    }
    // indegree array
    for(int c = 0; c < size; c++)
    {
        indegree[c] = 0;
    }
    for( int d = 0; d < size; d++)
    {
        for( int e = 0; e < size; e++)
        {
            if(matrix[d][e])
            {
                indegree[e] = indegree[e] + 1;
            }
        }
    }
    // stack array
    for( int f = 0; f < size; f++)
    {
        if( indegree[f] == 0)
        {
            stack[stackTop] = f;
            stackTop++;
        }
    }
    if( stackTop == 0)
    {
        printf("Topological sort is not possible for the given graph.\n");
        return -1;
    }
    // topological sort
    while( stackTop > 0)
    {
        stackTop--;
        temp = stack[stackTop];
        sorted[visited] = temp;
        visited++;
        for( int g = 0; g < size; g++)
        {
            if(matrix[temp][g])
            {
                indegree[g] = indegree[g] -1;
                if( indegree[g] == 0)
                {
                    stack[stackTop] = g;
                    stackTop++;
                }
            }
        }
    }
    if(visited != size)
    {
        printf("Topological sort is not possible for the given graph.\n");
        return -1;
    }
    // names array
    for( int h = 0; h < size; h++)
    {
        fscanf( nameFile, "%s", &name[0]);
        strcpy(names[h], name);
    }
    //output
    for( int i = 0; i < size; i++)
    {
        temp = sorted[i];
        strcpy(&name[0], names[temp]);
        fprintf(outputFile, "%s\n", name);
    }
    // clean up
    fclose(matrixFile);
    fclose(nameFile);
    fclose(outputFile);
    return 0;
}
