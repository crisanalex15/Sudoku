#include <stdio.h>
#include <stdlib.h>
#define N 9

int validare(int matrice[N][N], int i, int j)
{
    // pentru linii si coloane
    for (int ct = 0; ct < N; ct++) // Modificat indexarea de la 1 la 0
        if ((matrice[i][ct] == matrice[i][j] && ct != j) || (matrice[ct][j] == matrice[i][j] && ct != i))
            return 0;

    // pentru patratul 3x3
    int iStart = (i / 3) * 3; 
    int jStart = (j / 3) * 3; 

    for (int x = iStart; x < iStart + 3; x++)
        for (int y = jStart; y < jStart + 3; y++)
            if (matrice[x][y] == matrice[i][j] && (x != i || y != j))
                return 0;

    return 1; // Adăugat return 1 la final
}

int solutie(int iF, int iJ, int i, int j)
{
    if (i == iF && j == iJ)
        return 1;
    return 0;
}

void afisare(int matrice[N][N], int iF, int iJ)
{
    for (int i = 0; i < iF; i++) 
    {
        for (int j = 0; j < iJ; j++) 
            printf("%d ", matrice[i][j]);
        printf("\n");
    }
}

int rezolvareSudoku(int matrice[N][N], int i, int j, int iF, int jF, int Nr)
{
    if (i == iF) return 1; // Dacă am ajuns la finalul rândurilor, terminăm

    if (matrice[i][j] != 0) // Dacă celula este deja completată, trecem la următoarea
    {
        if (j + 1 < jF)
            return rezolvareSudoku(matrice, i, j + 1, iF, jF, Nr);
        else
            return rezolvareSudoku(matrice, i + 1, 0, iF, jF, Nr);
    }

    for (int ct = 1; ct <= N; ct++)
    {
        matrice[i][j] = ct;
        if (validare(matrice, i, j))
        {
            if (j + 1 < iF)
            {
                if (rezolvareSudoku(matrice, i, j + 1, iF, jF, Nr))
                    return 1;
            }
            else
            {
                if (rezolvareSudoku(matrice, i + 1, 0, iF, jF, Nr))
                    return 1;
            }
        }
        matrice[i][j] = 0; // Resetăm celula dacă soluția nu este validă
    }
    return 0; // Dacă nu găsim nicio valoare validă, întoarcem 0
}

int main()
{
    int sudoku[N][N] = {
        { 5, 3, 0, 0, 7, 0, 0, 0, 0 },
        { 6, 0, 0, 1, 9, 5, 0, 0, 0 },
        { 0, 9, 8, 0, 0, 0, 0, 6, 0 },
        { 8, 0, 0, 0, 6, 0, 0, 0, 3 },
        { 4, 0, 0, 8, 0, 3, 0, 0, 1 },
        { 7, 0, 0, 0, 2, 0, 0, 0, 6 },
        { 0, 6, 0, 0, 0, 0, 2, 8, 0 },
        { 0, 0, 0, 4, 1, 9, 0, 0, 5 },
        { 0, 0, 0, 0, 8, 0, 0, 7, 9 }
    };
    int iF = 9, jF = 9, Nr = 9;

    if (rezolvareSudoku(sudoku, 0, 0, iF, jF, Nr))
        afisare(sudoku, iF, jF);
    else
        printf("Nu exista solutie\n");

    return 0;
}
