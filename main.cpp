﻿#include <iostream>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <ctime>
#include <iostream>
using namespace std;

double** resolve_square_system(double** matrix, int columns, int &lines);
double** resolve_system(double** matrix, int columns, int &lines);
double* gaus_step_down(double** step_matrix, int lines, double* right_column);
double* gaus_step_up(double** step_matrix, int lines, double* right_column);
void transponir(double ** L, double *** LT, int columns, int lines);
double** fillRandMatrix(int* vars, int sizeVars, int lines);
double** fillsystem(int& lines, int& columns);
void print(double **A, int columns, int lines);
int* fill_vars(int n);

bool validate_chol(double** matrix, int lines, int columns);
double** cholesky_decomposition(double** matrix, int lines, int columns);
double determ(double** matrix, int *used, int columns, int current_line);

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
        FILE* file_matrix = fopen("/home/roman/matrix", "r");
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

// Проверка матрицы: положительно определённая?
bool validate_chol(double** matrix, int lines, int columns){
    // сравнение числа строк и столбцов
    if(lines != columns-1)
        return 0;
    // сравнение симметричных элементов
    for(int i = 0; i < lines; i++)
        for(int j = 0; j <= i; j++)
            if(matrix[i][j] != matrix[j][i])
                return 0;
    int* used = new int[lines];
    // хранит номера столбцов которые уже были в множителе
    if(matrix[0][0] < 0)
        return false;
    if((matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) < 0)
        return false;
    for(int i = 3; i <= lines; i++){
        memset(used, 0, sizeof(used));
        double sum = determ(matrix, used, i, 0);// подсчёт определителя
        printf( "DETERMINANT %d = %.2lf\n", i, sum);
        if(sum < 0) {
            delete [] used;
            return false;
        }
    }
    printf("\n");
    delete [] used;
    return true;
}

// Подсчёт определителя
double determ(double** matrix, int* used, int columns, int current_line){
    //условие конца рекурсии и её обратного хода
    if(current_line == columns - 3){
        int t[2]; // номера столбцов, которые не заняты
        int k = 0;
        for(int j = 0; j < columns-1 ; j++){
            if(used[j] != 1){
                t[k] = j;
                k++;
            }
        }
        double det2 = matrix[current_line][t[0]] * matrix[current_line + 1][t[1]] -
                matrix[current_line][t[1]] * matrix[current_line + 1][t[0]];
        return det2;
    }
    double temp = 0;
    // основное тело рекурсии
    for(int j = 0; j < columns-1; j++){
        if(used[j] != 1){
            used[j] = 1;
            int power = current_line + j;
            temp += matrix[current_line][j]*
                    determ(matrix, used, columns, current_line+1)*
                    pow(-1, power);
            used[j] = 0;
        }
    };
    return temp;
}

// Разложение Холецкого
double **cholesky_decomposition(double** matrix, int lines, int columns){
// выделение памяти
    double** L = (double**) malloc(sizeof(double*)*lines);
    L[0] = (double*) malloc(sizeof(double)*lines*lines);
    for(int i = 1; i < lines; i++)
        L[i] = *L + i*lines;
    memset(L[0],0, sizeof(double)*lines*lines);
// заполнение L
    L[0][0] = sqrt(matrix[0][0]);// первый угловой
    for(int i = 1; i < lines; i++){  // элементы первого столбца
        L[i][0] = matrix[i][0]/L[0][0];
    }
//основной цикл
    for(int i = 1; i < lines-1; i++){
        // вычисление элементов диагонали
        double temp = matrix[i][i];
        for(int k = 0; k < i; k++)
            temp -= L[i][k]*L[i][k];
        L[i][i] = sqrt(temp);
    // вычисление элементов строки следующей за вычисленным
    // элементом диагонали
        for(int p = 1; p <= i; p++){
            temp = matrix[i+1][p];
            for (int j = 0; j < p; j++){
                temp-=L[p][j]*L[i+1][j];
            }
            L[i+1][p] = temp/L[p][p];
        }
    }
     // вычисление последнего углового элемента
    double temp = matrix[lines-1][lines-1];
    for(int k = 0; k < lines-1; k++)
        temp -= L[lines-1][k]*L[lines-1][k];
    L[lines-1][lines-1] = sqrt(temp);
    return L;
}

// Решение ступенчатой матрицы нижнетреугольного вида
double* gaus_step_down(double** step_matrix, int lines, double* right_column){
    double* ar_value =(double*) malloc (sizeof(double)*lines);
    for(int i = 0; i < lines; i++){
        double temp = 0;
        for(int j = 0; j < i; j++)
            temp += ar_value[j]*step_matrix[i][j];
        ar_value[i] = (right_column[i] - temp)/step_matrix[i][i];
    }
    return ar_value;
}

// Решение ступенчатой матрицы верхнетреугольного вида
double* gaus_step_up(double** step_matrix, int lines, double* right_column){
    double* ar_value =(double*) malloc (sizeof(double)*lines);
    for(int i = lines-1; i >= 0; i--){
        double temp = 0;
        for(int j = lines-1; j > i; j--)
            temp += ar_value[j]*step_matrix[i][j];
        ar_value[i] = (right_column[i] - temp)/step_matrix[i][i];
    }
    return ar_value;
}

// Решение ступенчатой недоопределёной СЛУ
double** gaus_step_undeterm(double** matrix, int lines, int columns){
    int num_col = columns - lines;
    // выделение памяти
    double** values = (double**) malloc(sizeof(double*)*lines);
    values[0] = (double*) malloc(sizeof(double)*lines*num_col);
    for(int i = 1; i < lines; i++)
        values[i] = *values + i*num_col;
    memset(values[0], 0, sizeof(double)*lines*num_col);

    // заполнение массива решений
    for(int i = lines-1; i >= 0; i--){
        double temp = 0;
    //подсчёт константной части
        temp = matrix[i][columns-1];
        for(int k = lines -1; k > i; k--)
            temp -= matrix[i][k]*values[k][0];
        values[i][0] = temp/matrix[i][i];
    // подсчёт векторной части
        for(int j = 1; j < num_col; j++){
            temp = -matrix[i][lines-1+j];
            for(int k = lines -1; k > i; k--){
                temp -= matrix[i][k]*values[k][j];
            }
            values[i][j] = temp/matrix[i][i];
        }
        cout << endl;
    }
    return values;
}

// Транспонирование матрицы
void transponir(double** L, double *** LT, int columns, int lines){
// Выделение памяти
    *LT = (double**) malloc(sizeof(double*)*columns);
    (*LT)[0] = (double*) malloc(sizeof(double)*lines*columns);
    for(int i = 0; i < columns; i++)
        (*LT)[i] = *(*LT) + i*lines;
// Транспонирование
    for(int i = 0; i < lines; i++)
        for(int j = 0; j < columns; j++)
            (*LT)[j][i] = L[i][j];
}

// Решение квадратной системы
double **resolve_square_system(double** matrix, int columns, int& lines){
    int work_column = 0, f = 0;
    double temp;
    for(int base_line = 0; (base_line < lines) && (work_column < columns-1); base_line++){
        f = 0;
        // если система ЛЗ, т.е. самое угловое значение == 0, а строка ещё не последняя
        if((matrix[base_line][work_column] == 0) && (work_column == lines -1) ){
            lines = base_line;
            return gaus_step_undeterm(matrix, base_line, columns);
        }
        // обработка нулевых значений коэффициентов на углах, ищем хорошую строку
        if(floor( matrix[base_line][work_column] * 1000 + .5)/1000 == 0){ //округление до 3 знака
            int col = work_column;
            do {
                int j;
                for(j = base_line+1; j < lines; j++){
                    // строка найдена, перезапись
                    temp = matrix[j][col];
                    if(matrix[j][col] != 0){
                        double work;
                        for(int k = 0; k < columns; k++){
                            work = matrix[base_line][k];
                            matrix[base_line][k] = matrix[j][k];
                            matrix[j][k] = work;
                        }
                        f = 1;
                        break;
                    }
                }
                j--;// иначе может выйти за границы массива в коде ниже
                if((col == columns -2) && (matrix[j][columns-1] != 0))
                    return 0;
                if(f != 1) col++;
            } while((col < columns) && (temp == 0));
            work_column = col;
        }
        else temp = matrix[base_line][work_column];
        // определение множителя рабочей строки для каждого уравнения
        // и вычитание из всех строк рабочей
        for(int k = base_line+1; k < lines; k++){
            double factor = matrix[k][work_column]/matrix[base_line][work_column];
            int n;
            for(n = work_column; n < columns; n++){
                matrix[k][n] = matrix[k][n] - factor*matrix[base_line][n];
            }
        }
        print(matrix, columns, lines);
        // если все коэффициенты нули, а значение не равно нулю,
        // то не имеет решения
        if( (base_line != lines-1) && (work_column == columns -2) && (matrix[base_line+1][work_column] == 0) &&
                (matrix[base_line+1][columns-1] != 0))
            return 0;
        work_column++;
    }
    print(matrix, columns, lines);

    double** result = (double**) malloc(sizeof(double*));
    result[0] = (double*) malloc(sizeof(double)*lines);
    double* values = (double*) malloc(sizeof(double)*lines);
    for(int i = 0; i < lines; i ++)
        values[i] = matrix[i][columns-1];
    result[0] = gaus_step_up(matrix, lines, values);
    double** resultT;
    transponir(result, &resultT, lines, 1);
    return resultT;
}

// Решение неквадратной системы
double** resolve_system(double** matrix, int columns, int& lines){
    int work_column = 0, f = 0;
    double temp;
    for(int base_line = 0; base_line < lines; base_line++){
        f = 0;
        // если система ЛЗ, т.е. самое угловое значение == 0, а строка ещё не последняя
        if((floor(matrix[base_line][work_column] * 1000 + .5)/1000 == 0) && (work_column == columns -2) ){
            lines = base_line;
            return gaus_step_undeterm(matrix, lines, columns);
        }
        // обработка нулевых значений коэффициентов на углах, ищем хорошую строку
        if(floor( matrix[base_line][work_column] * 1000 + .5)/1000 == 0){ //округление до 3 знака
            int col = work_column;
            do {
                int j;
                for(j = base_line+1; j < lines; j++){
                    // строка найдена, перезапись
                    temp = matrix[j][col];
                    if(matrix[j][col] != 0){
                        double work;
                        for(int k = 0; k < columns; k++){
                            work = matrix[base_line][k];
                            matrix[base_line][k] = matrix[j][k];
                            matrix[j][k] = work;
                        }
                        f = 1;
                        break;
                    }
                }
                j--;// иначе может выйти за границы массива в коде ниже
                if((col == columns -2) && (matrix[j][columns-1] != 0))
                    return 0;
                if(f != 1) col++;
            } while((col < columns) && (temp == 0));
            work_column = col;
        }
        else temp = matrix[base_line][work_column];
        // определение множителя рабочей строки для каждого уравнения
        // и вычитание из всех строк рабочей
        for(int k = base_line+1; k < lines; k++){
            double factor = matrix[k][work_column]/matrix[base_line][work_column];
            int n;
            for(n = work_column; n < columns; n++){
                matrix[k][n] = matrix[k][n] - factor*matrix[base_line][n];
            }
        }
        print(matrix, columns, lines);
        // если все коэффициенты нули, а значение не равно нулю,
        // то не имеет решения
        if( (base_line != lines-1) && (work_column == columns -2) && (matrix[base_line+1][work_column] == 0) &&
                (matrix[base_line+1][columns-1] != 0))
            return 0;
        work_column++;
    }
    print(matrix, columns, lines);
    double** result = (double**) malloc(sizeof(double*)*lines);
    result[0] = (double*) malloc(sizeof(double)*lines*(columns-lines));
    for(int i = 1; i < lines; i++)
        result[i] = *result + (columns-lines)*i;
    result = gaus_step_undeterm(matrix, lines, columns);
    return result;
}

// Заполнение матрицы случайными числами
double** fillRandMatrix(int* vars, int columns, int lines){
    if(lines > columns-1) lines = columns-1;
    double** matrix = (double**) malloc(sizeof(double*)*lines);
    matrix[0] = (double*) malloc(sizeof(double)*lines*columns);
    for(int i = 1; i < lines; i++)
        matrix[i] = *matrix + columns*i;
    for(int i = 0; i < lines; i++)
        for(int j = 0; j < columns;j++){
            if(j==columns-1){
                double t =0;
                for(int j = 0; j < columns-1; j++)
                    t = t + matrix[i][j]*vars[j];
                matrix[i][columns-1] = t;
                break;
            }
            matrix[i][j] = rand()%9;
        }
    return matrix;
}

// Заполнение коэффициентов системы пользователем
double** fillsystem(int& lines, int& columns)
{
    int tempVolume = 0;
    printf("Введите число уравнений системы: ");
    scanf("%d", &lines);
    printf("Введите количество неизвестных : ");
    scanf("%d", &columns);
    columns++;
    double** matrix = (double**) malloc(sizeof(double*)*lines);
    matrix[0] = (double*) malloc(sizeof(double)*lines*columns);
    for(int i = 1; i < lines; i++)
        matrix[i] = *matrix + columns*i;
    for(int i = 0; i < lines; i++)
    {
        printf("Введите коэффициенты %d уравнения: ", i+1);
        fflush(stdout);
        for(int j = 0; j < columns; j++)
        {
            scanf("%d", &tempVolume);
            matrix[i][j] = tempVolume;
        }
    }
    return matrix;
}

// Вывод матрицы на экран
void print(double** A, int columns, int lines){
    for(int i = 0; i < lines; i++)
    {
        for(int j = 0; j < columns; j++)
            printf("%.2lf\t", A[i][j]);
        printf("%c", '\n');
    }
    std::cout << std::endl;
}

// Заполнение массива переменых пользователем
int* fill_vars(int n){
    int* vars = (int*) malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++)
    {
        printf("Введите значение %d переменной: ", i+1);
        scanf("%d", vars+i);
    }
    return vars;
}












