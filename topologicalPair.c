#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main( int argc, char *argv[])
{
    FILE *pairFile;
    FILE *sortedFile;
    int size = atoi(argv[3]);
    int stackTop = 0;
    int visited = 0;
    int count = 0;
    int temp;
    int index1;
    int index2;
    int indegree[size];
    int stack[size];
    int sorted[size];
    char name1[256];
    char name2[256];
    char names[size][256];
    bool matrix[size][size];
    // <exe> <pairFile> <sortedFile> <size>

    pairFile = fopen(argv[1], "r");
    sortedFile = fopen(argv[2], "w");
    if( pairFile == NULL)
    {
        printf("Could not open file.\n");
        return -1;
    }
    for( int a = 0; a < size; a++)
    {
        for( int b = 0; b < size; b++)
        {
            matrix[a][b] = false;
        }
    }
    while(!feof(pairFile))
    {
        index1 = -1;
        index2 = -1;
        fscanf( pairFile, "%s %s", &name1[0], &name2[0]);
        // names array
        for( int c = 0, d = 0; (c < count) && (d < 2); c++)
        {
            if(strcmp( name1, names[c]) == 0)
            {
                index1 = c;
                d++;
            }
            if(strcmp( name2, names[c]) == 0)
            {
                index2 = c;
                d++;
            }
        }
        if(index1 == -1)
        {
            strcpy(names[count], name1);
            index1 = count;
            count++;
        }
        if(index2 == -1)
        {
            strcpy(names[count], name2);
            index2 = count;
            count++;
        }
        // matrix array
        matrix[index1][index2] = true;
    }
    // indegree array
    for(int e = 0; e < size; e++)
    {
        indegree[e] = 0;
    }
    for( int f = 0; f < size; f++)
    {
        for( int g = 0; g < size; g++)
        {
            if(matrix[f][g])
            {
                indegree[g] = indegree[g] + 1;
            }
        }
    }
    // stack array
    for( int h = 0; h < size; h++)
    {
        if( indegree[h] == 0)
        {
            stack[stackTop] = h;
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
        for( int i = 0; i < size; i++)
        {
            if(matrix[temp][i])
            {
                indegree[i] = indegree[i] -1;
                if( indegree[i] == 0)
                {
                    stack[stackTop] = i;
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
    //output
    for( int i = 0; i < size; i++)
    {
        temp = sorted[i];
        strcpy(&name1[0], names[temp]);
        fprintf(sortedFile, "%s\n", name1);
    }
    // clean up
    fclose(pairFile);
    fclose(sortedFile);
    return 0;
}
