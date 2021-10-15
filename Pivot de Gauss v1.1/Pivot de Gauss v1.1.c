#include <stdio.h>
#include <stdlib.h>
#include "harshsinha03.c"


char variables[20] = "xyztabcdefghijklmnop";


struct Matrix
{
    int sizeX, sizeY;
    float value[20][21];
};


// Affiche la matrice.
void printf_matrix(struct Matrix matrix)
{
    for (int y = 0; y < matrix.sizeY; y++)
    {
        for (int x = 0; x < matrix.sizeX; x++)
            printf("%f\t", matrix.value[y][x]);

        printf("\n");
    }
}


// Demande à l'utilisateur la taille de la matrice.
void scanf_size_matrix(struct Matrix* matrix)
{
    printf("Nombre de variables = ");
    scanf_s("%d", &matrix->sizeX);
    matrix->sizeX += 1;
    printf("Nombre de lignes = ");
    scanf_s("%d", &matrix->sizeY);
    printf("\n");
}


// Demande à l'utilisateur les valeurs de la matrice.
void scanf_values_matrix(struct Matrix* matrix)
{
    for (int y = 0; y < matrix->sizeY; y++)
    {
        for (int x = 0; x < matrix->sizeX - 1; x++)
        {
            printf("L%d : %c = ", y + 1, variables[x]);
            scanf_s("%f", &matrix->value[y][x]);
        }

        printf("L%d = ", y + 1);
        scanf_s("%f", &matrix->value[y][matrix->sizeX - 1]);
        printf("\n");
    }
}


// Affiche les résultats (coefficients + variables).
void printf_results(struct Matrix matrix)
{
    for (int y = 0; y < matrix.sizeY; y++)
    {
        for (int x = 0; x < matrix.sizeX - 1; x++)
            if (matrix.value[y][x] != 0)
            {
                printf("(");
                frac(matrix.value[y][x]); // merci harshsinha03 ;)
                printf(") % c + ", variables[x]);
            }
        
        printf("0 = (%f)\n", matrix.value[y][matrix.sizeX - 1]);
    }
}


// Soustrait tous les éléments de la liste (1) par chaque valeur de la liste (2) * alpha.
void subtract_line(int line1, int line2, float alpha, struct Matrix* matrix)
{
    for (int x = 0; x < matrix->sizeX; x++)
        matrix->value[line1][x] -= matrix->value[line2][x] * alpha;
}


// Création d'un pivot.
void Pivot(int x, int y, struct Matrix* matrix)
{
    // [.., 1, ..]    [.., 1, ..]
    // [.., 2, ..] -> [.., 0, ..]
    // [.., 9, ..]    [.., 0, ..]

    for (int line = 0; line < matrix->sizeX; line++)
        if (line != y)
            if (matrix->value[line][x] != 0)
                subtract_line(line, y, matrix->value[line][x], matrix, matrix->sizeX);
}


// Divise tous les éléments d'une liste par une valeur.
void divide_list(float value, float list[], int sizeList)
{
    for (int i = 0; i < sizeList; i++)
        list[i] /= value;
}


// Vérifie si la valeur "value" est dans la liste.
int value_in_list(float value, float list[], int sizeList)
{
    for (int i = 0; i < sizeList; i++)
        if (list[i] == value)
            return 1;

    return 0;
}


// Remplace tous les éléments d'une liste par une même valeur.
void fill_list(float value, float list[], int sizeList)
{
    for (int i = 0; i < sizeList; i++)
        list[i] = value;
}


// Le programme commence ici :
int main()
{
    struct Matrix matrix;
    scanf_size_matrix(&matrix);
    scanf_values_matrix(&matrix);

    float linesExcept[20];
    fill_list(-1, linesExcept, matrix.sizeY);
    int cursor_linesExcept = 0;

    for (int x = 0; x < matrix.sizeX - 1; x++)
        for (int y = 0; y < matrix.sizeY; y++)
            if (!value_in_list(y, linesExcept, matrix.sizeY))
                if (matrix.value[y][x] != 0)
                {
                    divide_list(matrix.value[y][x], matrix.value[y], matrix.sizeX);
                    linesExcept[cursor_linesExcept] = y;
                    cursor_linesExcept += 1;
                    Pivot(x, y, &matrix);
                }

    printf_matrix(matrix);
    printf("\n");
    printf_results(matrix);
    printf("\n");
    system("pause");

    return 0;
}


// Program By Léonard Lemoosy.