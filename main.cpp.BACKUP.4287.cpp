#include <iostream>
#include <stdio.h>
#include <math.h>
<<<<<<< HEAD
=======
#include <rational.h>
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48
#include <string.h>
#include <stdio.h>
//#include <vector>
#include <ctime>
#include <iostream>
using namespace std;

double* resolve_square_system(double** matrix, int columns, int lines);
double** resolve_system(double** matrix, int columns, int lines);
double** fillRandMatrix(int* vars, int sizeVars, int lines);
double** fillsystem(int& lines, int& columns);
void print(double **A, int n, int m);
int* fill_vars(int n);

<<<<<<< HEAD
bool validate_chol(double** matrix, int lines, int columns);
//cholesky_decomposition(double** matrix, int lines, int columns);
double determ(double** matrix, int *used, int columns, int current_line);
=======
bool validate_chol(Ration** matrix, int lines, int columns);
//cholesky_decomposition(Ration** matrix, int lines, int columns);
Ration determ(Ration** matrix, int *used, int columns, int current_line);
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48

int main()
{
    srand(time(0));
    int lines = 1, columns = 2;
    printf("Выберите способ заполнения матрицы:\n r - случаные коэффициенты\n");
    printf(" s - всю матрицу заполнить самостоятельно\n");
    printf(" f - заполнить матрицу из файла\n");
    char choice = 'r';
    scanf("%c", &choice);
<<<<<<< HEAD
    double** matrix;
=======
    Ration** matrix;
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48

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
<<<<<<< HEAD
        }
        break;
    case 'f':{
=======
    }
        break;
    case 'f':
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48
        FILE* file_matrix = fopen("/home/roman/matrix", "r");
        if(NULL == file_matrix){
            printf("error fopen()\n");
        }
        fscanf(file_matrix, "%d %d", &lines, &columns);
<<<<<<< HEAD
        double** matrix = (double**) malloc(sizeof(double*)*lines);
        matrix[0] = (double*) malloc(sizeof(double)*lines*columns);
=======
        Ration** matrix = (Ration**) malloc(sizeof(Ration*)*lines);
        matrix[0] = (Ration*) malloc(sizeof(Ration)*lines*columns);
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48
        for(int i = 1; i < lines; i++)
            matrix[i] = *matrix + columns*i;
        int temp;
        for(int i = 0; i < lines; i++)
            for(int j = 0; j < columns; j++){
                fscanf(file_matrix, "%d", &temp);
                matrix[i][j] = temp;
            };
        fclose(file_matrix);
        print(matrix, columns, lines);
        columns--;
<<<<<<< HEAD
        }
        break;
    }

    if(validate_chol(matrix, lines, columns));
        //cholesky_decomposition(matrix);
    double** result;
    double* res;
=======
        break;
    }
    if(validate_chol(matrix, lines, columns));
        //cholesky_decomposition(matix);
    Ration** result;
    Ration* res;
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48
    if(lines != columns - 1)
        result = resolve_system(matrix, columns, lines);
    else res = resolve_square_system(matrix, columns, lines);
    if(result == 0 or res == 0)
    {
        printf("Система не имеет решений!\n");
        std::cin.get();
        return 0;
    }
    if(lines != columns - 1){
        for(int i = 0; i < lines; i++){
            cout << "X" << i+1 << " = " << result[i][columns -1 - lines] << " + ";
            for(int j = 0; j < columns - 1 - lines; j++ ){
                cout << -result[i][j] << " * X" << lines+1+j;
                if(j != columns - 1 - lines -1)
                    cout << "\t+ ";
            }
            cout << endl;
        }
    }
    else{
        for(int i = 0; i < lines; i++)
        cout << "x" << i+1 << " = " << res[i] << "\n";
        cout << endl;
    };
    free(matrix[0]);
    free(matrix);
    std::cin.get();
}

<<<<<<< HEAD
bool validate_chol(double** matrix, int lines, int columns){
=======
bool validate_chol(Ration** matrix, int lines, int columns){
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48
    if(lines != columns)
        return 0;
    for(int i = 0; i < lines; i++)
        for(int j = 0; j <= i; j++)
            if(matrix[i][j] != matrix[j][i])
                return 0;
    int* used = new int(lines);
    memset(used, 0, sizeof(used));
<<<<<<< HEAD
    double sum = determ(matrix, used, columns, 0);
=======
    Ration sum = determ(matrix, used, columns, 0);
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48
    delete used;
    cout << sum << endl;
    if(sum > 0) return true;
    else return false;
}

<<<<<<< HEAD
double determ(double** matrix, int* used, int columns, int current_line){
    double temp;
=======
Ration determ(Ration** matrix, int* used, int columns, int current_line){
    Ration temp;
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48
    for(int j = 0; j < columns; j++){
        if(used[j] == 0){
            used[j] = 1;
            temp = matrix[current_line][j]*
                    determ(matrix, used, columns, current_line+1)*
                    pow(-1, current_line + j);
            used[j] = 0;
        }
    }
    return temp;
}

<<<<<<< HEAD
/*cholesky_decomposition(double** matrix, int lines, int columns){

}*/

double* resolve_square_system(double** matrix, int columns, int lines){
    int work_column = 0, f = 0;
    double temp;
=======
/*cholesky_decomposition(Ration** matrix, int lines, int columns){

}*/

Ration* resolve_square_system(Ration** matrix, int columns, int lines){
    int work_column = 0, f = 0;
    Ration temp;
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48
    for(int i = 0; (i < lines) && (work_column < columns-1); i++){
        f = 0;
        print(matrix, columns, lines);
        // обработка нулевых значений коэффициентов на углах, ищем хорошую строку
        if(matrix[i][work_column] == 0){
            int col = work_column;
            do {
                int j;
                for(j = i+1; j < lines; j++){
                    // строка найдена, перезапись
<<<<<<< HEAD
                    temp = matrix[j][col];
                    if(matrix[j][col] != 0){
                        double work;
=======
                    temp = matrix[j][col].numer();
                    if(matrix[j][col].numer() != 0){
                        Ration work;
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48
                        for(int k = 0; k < columns; k++){
                            work = matrix[i][k];
                            matrix[i][k] = matrix[j][k];
                            matrix[j][k] = work;
                        }
                        f = 1;
                        break;
                    }
                }
<<<<<<< HEAD
                j--;// иначе может выйти за границы массива в коде ниже
                if((col == columns -2) && (matrix[j][columns-1] != 0))
                    return 0;
                if(f != 1) col++;
            } while((col < columns) && (temp == 0));
=======
                if((col == columns -2) && (matrix[j][columns-1].numer() != 0))
                    return 0;
                if(f != 1) col++;
            } while((col < columns) && (temp.numer() == 0));
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48
            work_column = col;
        }
        else temp = matrix[i][work_column];
        // деление всех коэффициентов на крайний левый на рабочей строке
        for(int j = 0; j < columns; j++)
            matrix[i][j] = matrix[i][j]/temp;
        // определение множителя рабочей строки для каждого уравнения
        // и вычитание из всех строк рабочей
        for(int k = 0; k < lines; k++){
            if(k==i) continue;
<<<<<<< HEAD
            double factor = matrix[k][work_column];
=======
            Ration factor = matrix[k][work_column];
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48
            int n;
            for(n = 0; n < columns; n++){
                matrix[k][n] = matrix[k][n] - factor*matrix[i][n];
            }
        }
        print(matrix, columns, lines);
        // если все коэффициенты нули, а значение не равно нулю,
        // то не имеет решения
<<<<<<< HEAD
        if( (i != lines-1) && (work_column == columns -2) && (matrix[i+1][work_column] == 0) &&
                (matrix[i+1][columns-1] != 0))
=======
        if( (i != lines-1) && (work_column == columns -2) && (matrix[i+1][work_column].numer() == 0) &&
                (matrix[i+1][columns-1].numer() != 0))
>>>>>>> 68c520251d66a7f730d0301f23fd17d0df836e48
            return 0;
        work_column++;
    }
    print(matrix, columns, lines);
    double* result = (double*) malloc(sizeof(double)*lines);
    for(int i = 0; i < lines; i++)
        result[i] = matrix[i][columns-1];
    return result;
}

double** resolve_system(double** matrix, int columns, int lines){
    int work_column = 0, f = 0;
    double temp;
    for(int i = 0; i < lines; i++){
        f = 0;
        print(matrix, columns, lines);
        // обработка нулевых значений коэффициентов на углах, ищем хорошую строку
        if(matrix[i][work_column] == 0){
            int col = work_column;
            do {
                for(int j = i+1; j < lines; j++){
                    if(matrix[j][col]  != 0){ // строка найдена, перезапись
                        temp = matrix[j][col] ;
                        double work;
                        for(int k = 0; k < columns; k++){
                            work = matrix[i][k];
                            matrix[i][k] = matrix[j][k];
                            matrix[j][k] = work;
                        }
                        print(matrix, columns, lines);
                        break;
                    }
                }
                if(col == columns -2)
                    return 0;
                if(f != 1) col++;
            } while((col < columns) && (temp == 0));
            work_column = col;
        }
        else temp = matrix[i][work_column];
        // деление всех коэффициентов на крайний левый на рабочей строке
        for(int j = 0; j < columns; j++)
            matrix[i][j] = matrix[i][j]/temp;
        // определение множителя рабочей строки для каждого уравнения
        // и вычитание из всех строк рабочей
        for(int k = 0; k < lines; k++){
            if(k==i) k++;
            double factor = matrix[k][work_column];
            for(int n = 0; n < columns; n++){
                matrix[k][n] = matrix[k][n] - factor*matrix[i][n];
            }
        }
        work_column++;
    }
    print(matrix, columns, lines);
    double** result = (double**) malloc(sizeof(double*)*lines);
    result[0] = (double*) malloc(sizeof(double)*lines*(columns-lines));
    for(int i = 1; i < lines; i++)
        result[i] = *result + (columns-lines)*i;
    for(int i = 0; i < lines; i++){
       for(int j = 0; j < columns-lines; j++)
           result[i][j] = matrix[i][lines + j];
    }
    return result;
}

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

void print(double** A, int n, int m){
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












