#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <ctime>
#include <iostream>
#include "title.h"
using namespace std;

int main()
{
    srand(time(0));
    int lines = 1, columns = 2;
    printf("Выберите способ заполнения матрицы:\n r - случаные коэффициенты\n");
    printf(" s - всю матрицу заполнить самостоятельно\n");
    printf(" f - заполнить матрицу из файла\n");
    char choice = 'r';
    scanf("%c", &choice);
    double** matrix;

    switch (choice){
    case 's':
        matrix = fillsystem(lines, columns);
        break;
    case 'r':{
        printf("Enter number of variables: ");
        scanf("%d", &columns);
        columns++;
        int* vars = fill_vars(columns-1);
        printf("Enter number of equations: ");
        scanf("%d", &lines);
        matrix = fillRandMatrix(vars, columns, lines);
        }
        break;
    case 'f':{
        char filename[120];
        printf("Формат файла: первые 2 числа - количество строк и столбцов, затем коэффициенты\n");
        printf("Введите полный путь к файлу: ");
        scanf("%s", filename);
        FILE* file_matrix = fopen(filename, "r");
        if(NULL == file_matrix){
            printf("error fopen()\n");
        }
        fscanf(file_matrix, "%d %d", &lines, &columns);
        matrix = (double**) malloc(sizeof(double*)*lines);
        matrix[0] = (double*) malloc(sizeof(double)*lines*columns);
        for(int i = 1; i < lines; i++)
            matrix[i] = *matrix + columns*i;
        double temp;
        for(int i = 0; i < lines; i++)
            for(int j = 0; j < columns; j++){
                fscanf(file_matrix, "%lf", &temp);
                matrix[i][j] = temp;
            };
        fclose(file_matrix);
        print(matrix, columns, lines);
        }
        break;
    }

    if(validate_chol(matrix, lines, columns)){
        printf("Матрица симметричная положительная определённая\n\n");
        double** L;
        L = cholesky_decomposition(matrix, lines, columns);
        print(L, lines, lines);
        double* right_part =(double*) malloc (sizeof(double)*lines);
        for (int i = 0; i < lines; i ++)
            right_part[i] = matrix[i][columns-1];
        double* values_y = gaus_step_down(L, lines, right_part);
        for (int i = 0; i < lines; i ++)
            printf("y%d = %.2lf\n", i+1, values_y[i]);
        printf("\n");
        double** LT;
        transponir(L, &LT, lines, lines);
        print(LT, lines, lines);
        double* values_x = gaus_step_up(LT, lines, values_y);
        for (int i = 0; i < lines; i ++)
            printf("x%d = %.2lf\n", i+1, values_x[i]);
        printf("\n");
        free(L[0]);
        free(LT[0]);
        free(L);
        free(LT);
        free(values_y);
        free(values_x);
        free(matrix[0]);
        free(matrix);
        return 0;
    }
    double** result;
    if(lines != columns - 1)
        result = resolve_system(matrix, columns, lines);
    else result = resolve_square_system(matrix, columns, lines);
    if(result == 0)
    {
        printf("Система не имеет решений!\n");
        std::cin.get();
        return 0;
    }
    char c;
    int factor = 0;
    for(int i = 0; i < lines; i++){
        printf("X%d = %.2lf", i+1, result[i][0]);
        for(int j = 1; j < columns - lines; j++ ){
            if(result[i][j] >= 0) {
                c = '+';
                factor = 1;}
            else {
                c = '-';
                factor = -1;}
            printf(" %c %.2lf*X%d", c, result[i][j]*factor, lines+j);
        }
        cout << endl;
    }
    free(result[0]);
    free(result);
    free(matrix[0]);
    free(matrix);
    std::cin.get();
}













