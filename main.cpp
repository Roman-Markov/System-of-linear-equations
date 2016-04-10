#include <iostream>
#include <stdio.h>
#include <math.h>
#include <rational.h>
#include <vector>
using namespace std;

int** fillmatrix(int* vars, int sizeVars, int lines);
void print(int** A, int n, int m);
int* fill_vars(int n);
int main()
{
    int vars_size = 1;
    printf("Enter number of variables: ");
    scanf("%d", &vars_size);
    int* vars = fill_vars(vars_size);
    printf("Enter number of lines: ");
    int lines = 1;
    scanf("%d", &lines);
    int** matrix = fillmatrix(vars, vars_size, lines);
    print(matrix, vars_size+1, lines);
    free(vars);
    free(matrix[0]);
    free(matrix);
    std::cin.get();
}

int** fillmatrix(int* vars, int sizeVars, int lines){
    int** matrix = (int**) malloc(sizeof(int*)*lines);
    matrix[0] = (int*) malloc(sizeof(int)*lines*(sizeVars+1));
    for(int i = 1; i < lines; i++)
        matrix[i] = *matrix + (sizeVars+1)*i;
    for(int i = 0; i < lines; i++)
        for(int j = 0; j < (sizeVars+1);j++){
            if(j==sizeVars){
                int t =0;
                for(int j = 0; j < sizeVars; j++)
                    t += matrix[i][j];
                matrix[i][sizeVars] = t;
                break;
            }
            matrix[i][j] = vars[j]*rand()%9;
        }
    return matrix;
}

void print(int** A, int n, int m){
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            printf("%d ", A[i][j]);
        printf("%c", '\n');
    }
}

int* fill_vars(int n){
    int* vars = (int*) malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++)
        scanf("%d", vars+i);
    return vars;
}










