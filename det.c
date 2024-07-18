#include <stdio.h>
#include <stdlib.h>

void process();

double det(double **matrix, int n);

int input(double ***matrix, int *m, int *n);
void output(double det);

void init_matrix(double ***matrix, int m, int n);

int main() {
    process();

    return 0;
}

void process() {
    double **data = NULL;
    int m = 0, n = 0;
    double res = 0;

    if (input(&data, &m, &n)) {
        res = det(data, n);
        output(res);

    } else
        printf("n/a");

    if (data != NULL) free(data);
}

double det(double **matrix, int n) {
    double d = 1;
    double perms = 1;

    // through columns / width
    for (int j = 0; j < n; j++) {
        // int level = 0;  // the level that algrorithm starts

        for (int i = j + 1; i < n; i++) {
            if ((matrix[j][j] == 0) && (matrix[i][j] != 0)) {
                for (int row = 0; row < n; row++) {
                    double buff = matrix[i][row];
                    matrix[i][row] = matrix[j][row];
                    matrix[j][row] = buff;
                }
                perms *= -1;
                break;
            }
        }

        if (matrix[j][j] != 0) {
            // through rows / height
            for (int i = j + 1; i < n; i++) {
                double elem = matrix[i][j];

                double coef = elem / matrix[j][j];

                for (int row = 0; row < n; row++) {
                    matrix[i][row] -= (coef * matrix[j][row]);
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        d *= matrix[i][i];
    }

    if (d == -0.0) d *= -1;

    return d * perms;
}

int input(double ***matrix, int *m, int *n) {
    int f = 1;

    if (scanf("%d", m) != 1 || scanf("%d", n) != 1 || (*m) != (*n) || (*m) <= 0 || (*n) <= 0) {
        f = 0;
    } else {
        init_matrix(matrix, *m, *n);

        for (int i = 0; i < (*m); i++)
            for (int j = 0; j < (*n); j++)
                if (scanf("%lf", &((*matrix)[i][j])) != 1) f = 0;
    }
    return getchar() == '\n' ? f : 0;
}

void output(double res) { printf("%.6lf", res); }

void init_matrix(double ***matrix, int m, int n) {
    (*matrix) = malloc(m * n * sizeof(double) + m * sizeof(double *));
    double *ptr = (double *)((*matrix) + m);
    for (int i = 0; i < m; i++) (*matrix)[i] = ptr + n * i;
}