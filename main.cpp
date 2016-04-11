#include <iostream>
#include <stdio.h>
#include <math.h>
#include <rational.h>
#include <vector>
using namespace std;

Ration** fillmatrix(int* vars, int sizeVars, int lines);
void print(Ration **A, int n, int m);
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
    Ration** matrix = fillmatrix(vars, vars_size, lines);
    print(matrix, vars_size+1, lines);
    free(vars);
    free(matrix[0]);
    free(matrix);
    std::cin.get();
}









Ration** fillmatrix(int* vars, int sizeVars, int lines){
    Ration** matrix = (Ration**) malloc(sizeof(Ration*)*lines);
    matrix[0] = (Ration*) malloc(sizeof(Ration)*lines*(sizeVars+1));
    for(int i = 1; i < lines; i++)
        matrix[i] = *matrix + (sizeVars+1)*i;
    for(int i = 0; i < lines; i++)
        for(int j = 0; j < (sizeVars+1);j++){
            if(j==sizeVars){
                Ration t =0;
                for(int j = 0; j < sizeVars; j++)
                    t = t + matrix[i][j];
                matrix[i][sizeVars] = t;
                break;
            }
            matrix[i][j] = vars[j]*rand()%9;
        }
    return matrix;
}

void print(Ration** A, int n, int m){
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            cout << A[i][j] << " ";
        printf("%c", '\n');
    }
}

int* fill_vars(int n){
    int* vars = (int*) malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++)
        scanf("%d", vars+i);
    return vars;
}










