#include <iostream>
#include <stdio.h>
#include <math.h>
#include <rational.h>
#include <vector>
#include <ctime>
using namespace std;

Ration *resolve_system(Ration** matrix, int columns, int lines);
Ration** fillmatrix(int* vars, int sizeVars, int lines);
void print(Ration **A, int n, int m);
int* fill_vars(int n);
int main()
{
    srand(time(0));
    int vars_size = 1;
    printf("Enter number of variables: ");
    scanf("%d", &vars_size);
    int* vars = fill_vars(vars_size);
    printf("Enter number of lines: ");
    int lines = 1;
    scanf("%d", &lines);
    Ration** matrix = fillmatrix(vars, vars_size, lines);
    //print(matrix, vars_size+1, lines);
    resolve_system(matrix, vars_size+1, lines);
    free(vars);
    free(matrix[0]);
    free(matrix);
    std::cin.get();
}

Ration* resolve_system(Ration** matrix, int columns, int lines){
    int work_column = 0;
    for(int i = 0; i < lines; i++){
        print(matrix, columns, lines);
        for(int j = i; j < columns; j++){
          // обработка нулевых значений коэффициентов на углах, ищем хорошую строку
            if(matrix[i][work_column].numer() == 0){
                for(int j = i+1; j < lines; j++){
                    if(matrix[j][work_column].numer() != 0){ // строка найдена, перезапись
                        Ration* work = (Ration*) malloc(sizeof(Ration)*columns);
                        for(int k = 0; k < columns; k++){
                            work[k] = matrix[i][k];
                            matrix[i][k] = matrix[j][k];
                            matrix[j][k] = work[k];
                        }
                        free(work);
                        break;
                    }
                }
            }
            Ration temp = matrix[i][work_column];
            // деление всех коэффициентов на крайний левый на рабочей строке
            for(int j = i; j < columns; j++)
                matrix[i][j] = matrix[i][j]/temp;
            // определение множителя рабочей строки для каждой следующей
            // и вычитание из всех строк рабочей
            if(i != lines-1){
                for(int k = i+1; k < lines; k++){
                    Ration factor = matrix[k][work_column];
                    for(int n = work_column; n < columns; n++){
                        matrix[k][n] = matrix[k][n] - factor*matrix[i][n];
                    }
                }
            }
        }
        work_column++;
    }
    print(matrix, columns, lines);
    Ration* result = (Ration*) malloc(sizeof(int)*lines);
    for(int i = 0; i < lines; i++)
        result[i] = matrix[i][columns-1];
    return result;
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
                    t = t + matrix[i][j]*vars[j];
                matrix[i][sizeVars] = t;
                break;
            }
            matrix[i][j] = rand()%9;
        }
    return matrix;
}

void print(Ration** A, int n, int m){
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < n; j++)
            cout << A[i][j] << "\t";
        printf("%c", '\n');
    }
    std::cout << std::endl;
}

int* fill_vars(int n){
    int* vars = (int*) malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++)
        scanf("%d", vars+i);
    return vars;
}










