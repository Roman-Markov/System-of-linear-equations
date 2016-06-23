#include <iostream>
#include <stdio.h>
#include <math.h>
#include <rational.h>
#include <string.h>
#include <stdio.h>
//#include <vector>
#include <ctime>
#include <iostream>
using namespace std;

Ration* resolve_square_system(Ration** matrix, int columns, int lines);
Ration** resolve_system(Ration** matrix, int columns, int lines);
Ration** fillRandMatrix(int* vars, int sizeVars, int lines);
Ration** fillsystem(int& lines, int& columns);
void print(Ration **A, int n, int m);
int* fill_vars(int n);

bool validate_chol(Ration** matrix, int lines, int columns);
//cholesky_decomposition(Ration** matrix, int lines, int columns);
Ration determ(Ration** matrix, int *used, int columns, int current_line);

int main()
{
    srand(time(0));
    int lines = 1, columns = 2;
    printf("Выберите способ заполнения матрицы:\n r - случаные коэффициенты\n");
    printf(" s - всю матрицу заполнить самостоятельно\n");
    printf(" f - заполнить матрицу из файла\n");
    char choice = 'r';
    scanf("%c", &choice);
    Ration** matrix;

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
    case 'f':
        FILE* file_matrix = fopen("/home/roman/matrix", "r");
        if(NULL == file_matrix){
            printf("error fopen()\n");
        }
        fscanf(file_matrix, "%d %d", &lines, &columns);
        Ration** matrix = (Ration**) malloc(sizeof(Ration*)*lines);
        matrix[0] = (Ration*) malloc(sizeof(Ration)*lines*columns);
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
        break;
    }
    if(validate_chol(matrix, lines, columns));
        //cholesky_decomposition(matix);
    Ration** result;
    Ration* res;
    if(lines != columns - 1)
        result = resolve_system(matrix, columns, lines);
    else res = resolve_square_system(matrix, columns, lines);
    if(result == 0 or res == 0)
    {
        printf("Система не имеет решений!\n");
        std::cin.get();
        return 0;
    }
    if(lines != columns - 1)
    {
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
    }
    free(matrix[0]);
    free(matrix);
    std::cin.get();
}

bool validate_chol(Ration** matrix, int lines, int columns){
    if(lines != columns)
        return 0;
    for(int i = 0; i < lines; i++)
        for(int j = 0; j <= i; j++)
            if(matrix[i][j] != matrix[j][i])
                return 0;
    int* used = new int(lines);
    memset(used, 0, sizeof(used));
    Ration sum = determ(matrix, used, columns, 0);
    delete used;
    cout << sum << endl;
    if(sum > 0) return true;
    else return false;
}

Ration determ(Ration** matrix, int* used, int columns, int current_line){
    Ration temp;
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

/*cholesky_decomposition(Ration** matrix, int lines, int columns){

}*/

Ration* resolve_square_system(Ration** matrix, int columns, int lines){
    int work_column = 0, f = 0;
    Ration temp;
    for(int i = 0; (i < lines) && (work_column < columns-1); i++){
        f = 0;
        print(matrix, columns, lines);
        // обработка нулевых значений коэффициентов на углах, ищем хорошую строку
        if(matrix[i][work_column].numer() == 0){
            int col = work_column;
            do {
                int j;
                for(j = i+1; j < lines; j++){
                    // строка найдена, перезапись
                    temp = matrix[j][col].numer();
                    if(matrix[j][col].numer() != 0){
                        Ration work;
                        for(int k = 0; k < columns; k++){
                            work = matrix[i][k];
                            matrix[i][k] = matrix[j][k];
                            matrix[j][k] = work;
                        }
                        f = 1;
                        break;
                    }
                }
                if((col == columns -2) && (matrix[j][columns-1].numer() != 0))
                    return 0;
                if(f != 1) col++;
            } while((col < columns) && (temp.numer() == 0));
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
            Ration factor = matrix[k][work_column];
            int n;
            for(n = 0; n < columns; n++){
                matrix[k][n] = matrix[k][n] - factor*matrix[i][n];
            }
        }
        print(matrix, columns, lines);
        // если все коэффициенты нули, а значение не равно нулю,
        // то не имеет решения
        if( (i != lines-1) && (work_column == columns -2) && (matrix[i+1][work_column].numer() == 0) &&
                (matrix[i+1][columns-1].numer() != 0))
            return 0;
        work_column++;
    }
    print(matrix, columns, lines);
    Ration* result = (Ration*) malloc(sizeof(int)*lines);
    for(int i = 0; i < lines; i++)
        result[i] = matrix[i][columns-1];
    return result;
}

Ration** resolve_system(Ration** matrix, int columns, int lines){
    int work_column = 0, f = 0;
    Ration temp;
    for(int i = 0; i < lines; i++){
        f = 0;
        print(matrix, columns, lines);
        // обработка нулевых значений коэффициентов на углах, ищем хорошую строку
        if(matrix[i][work_column].numer() == 0){
            int col = work_column;
            do {
                for(int j = i+1; j < lines; j++){
                    if(matrix[j][col].numer() != 0){ // строка найдена, перезапись
                        temp = matrix[j][col].numer();
                        Ration work;
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
            } while((col < columns) && (temp.numer() == 0));
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
            Ration factor = matrix[k][work_column];
            for(int n = 0; n < columns; n++){
                matrix[k][n] = matrix[k][n] - factor*matrix[i][n];
            }
        }
        work_column++;
    }
    print(matrix, columns, lines);
    Ration** result = (Ration**) malloc(sizeof(Ration*)*lines);
    result[0] = (Ration*) malloc(sizeof(Ration)*lines*(columns-lines));
    for(int i = 1; i < lines; i++)
        result[i] = *result + (columns-lines)*i;
    for(int i = 0; i < lines; i++){
       for(int j = 0; j < columns-lines; j++)
           result[i][j] = matrix[i][lines + j];
    }
    return result;
}

Ration** fillRandMatrix(int* vars, int columns, int lines){
    if(lines > columns-1) lines = columns-1;
    Ration** matrix = (Ration**) malloc(sizeof(Ration*)*lines);
    matrix[0] = (Ration*) malloc(sizeof(Ration)*lines*columns);
    for(int i = 1; i < lines; i++)
        matrix[i] = *matrix + columns*i;
    for(int i = 0; i < lines; i++)
        for(int j = 0; j < columns;j++){
            if(j==columns-1){
                Ration t =0;
                for(int j = 0; j < columns-1; j++)
                    t = t + matrix[i][j]*vars[j];
                matrix[i][columns-1] = t;
                break;
            }
            matrix[i][j] = rand()%9;
        }
    return matrix;
}
Ration** fillsystem(int& lines, int& columns)
{
    int tempVolume = 0;
    printf("Введите число уравнений системы: ");
    scanf("%d", &lines);
    printf("Введите количество неизвестных : ");
    scanf("%d", &columns);
    columns++;
    Ration** matrix = (Ration**) malloc(sizeof(Ration*)*lines);
    matrix[0] = (Ration*) malloc(sizeof(Ration)*lines*columns);
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










