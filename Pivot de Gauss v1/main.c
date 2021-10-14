#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "harshsinha03.c"


char variables[20] = "xyztabcdefghijklmnop";


// Affiche la matrice.
void printf_matrix(float matrix[][20], int sizeX, int sizeY)
{
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX; x++)
            printf("%f\t", matrix[y][x]);

        printf("\n");
    }
}

// Demande à l'utilisateur la taille de la matrice.
void scanf_sizes_matrix(int* sizeX, int* sizeY)
{
    printf("sizeX = ");
    scanf_s("%d", sizeX);
    printf("sizeY = ");
    scanf_s("%d", sizeY);
    printf("\n");
}

// Demande à l'utilisateur les valeurs de la matrice.
void scanf_values_matrix(float matrix[][20], int sizeX, int sizeY)
{
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX - 1; x++)
        {
            printf("line (%d) -> %c = ", y + 1, variables[x]);
            scanf_s("%f", &matrix[y][x]);
        }

        printf("line (%d) -> TOTAL = ", y + 1);
        scanf_s("%f", &matrix[y][sizeX - 1]);
        printf("\n");
    }
}

// Affiche les résultats (coefficients + variables).
void printf_results(float matrix[][20], int sizeX, int sizeY)
{
    for (int y = 0; y < sizeY; y++)
    {
        for (int x = 0; x < sizeX - 1; x++)
            if (matrix[y][x] != 0)
            {
                printf("(");
                frac(matrix[y][x]); // merci harshsinha03 ;)
                printf(") % c + ", variables[x]);
            }
        
        printf("0 = (%f)\n", matrix[y][sizeX - 1]);
    }
}

// Soustrait tous les éléments de la liste (1) par chaque valeur de la liste (2) * alpha.
void subtract_line(int line1, int line2, float alpha, float matrix[][20], int sizeX)
{
    for (int x = 0; x < sizeX; x++)
        matrix[line1][x] -= matrix[line2][x] * alpha;
}

// Création d'un pivot.
void Pivot(int x, int y, float matrix[][20], int sizeX, int sizeY)
{
    // [.., 1, ..]    [.., 1, ..]
    // [.., 2, ..] -> [.., 0, ..]
    // [.., 9, ..]    [.., 0, ..]

    for (int line = 0; line < sizeX; line++)
        if (line != y)
            if (matrix[line][x] != 0)
                subtract_line(line, y, matrix[line][x], matrix, sizeX);
}

// Divise tous les éléments d'une liste par une valeur.
void divide_list(float value, float list[], int sizeList)
{
    for (int i = 0; i < sizeList; i++)
        list[i] /= value;
}

// Remplace tous les éléments d'une liste par une même valeur.
void fill_list(float value, float list[], int sizeList)
{
    for (int i = 0; i < sizeList; i++)
        list[i] = value;
}

// Vérifie si la valeur "value" est dans la liste.
int value_in_list(float value, float list[], int sizeList)
{
    for (int i = 0; i < sizeList; i++)
        if (list[i] == value)
            return 1;

    return 0;
}

// Le programme commence ici :
int main()
{
    int sizeX, sizeY;
    float matrix[20][20];
    float linesExcept[20];
    int cursor_linesExcept = 0;

    scanf_sizes_matrix(&sizeX, &sizeY);
    fill_list(-1.0, linesExcept, sizeY);
    scanf_values_matrix(matrix, sizeX, sizeY);

    for (int x = 0; x < sizeX - 1; x++)
        for (int y = 0; y < sizeY; y++)

            if (!value_in_list(y, linesExcept, sizeY))

                if (matrix[y][x] != 0)
                {
                    divide_list(matrix[y][x], matrix[y], sizeX);
                    linesExcept[cursor_linesExcept] = y;
                    cursor_linesExcept += 1;
                    Pivot(x, y, matrix, sizeX, sizeY);

                    if (linesExcept[sizeY - 1] != -1.0f)
                        x = sizeX;

                    break;
                }

    printf_matrix(matrix, sizeX, sizeY);
    printf("\n");
    printf_results(matrix, sizeX, sizeY);
    printf("\n");
    system("pause");

    return 0;
}