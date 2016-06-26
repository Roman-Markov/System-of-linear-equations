#ifndef TITLE_H
#define TITLE_H

double** resolve_square_system(double** matrix, int columns, int &lines);
double** resolve_system(double** matrix, int columns, int &lines);
double* gaus_step_down(double** step_matrix, int lines, double* right_column);
double* gaus_step_up(double** step_matrix, int lines, double* right_column);
void transponir(double ** L, double *** LT, int columns, int lines);
double** fillRandMatrix(int* vars, int sizeVars, int lines);
double** fillsystem(int& lines, int& columns);
void improve_matrix(double*** matrix, int lines, int columns);
void print(double **A, int columns, int lines);
int* fill_vars(int n);

bool validate_chol(double** matrix, int lines, int columns);
double** cholesky_decomposition(double** matrix, int lines, int columns);
double determ(double** matrix, int *used, int columns, int current_line);

#endif // TITLE_H

