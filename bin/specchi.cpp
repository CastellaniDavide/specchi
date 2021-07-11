#include <bits/stdc++.h>
using namespace std;

typedef enum
{
    SOPRA = 0,
    DESTRA = 1,
    SOTTO = 2,
    SINISTRA = 3
} parete_t; // lato

typedef struct
{
    parete_t lato;
    int posizione;
} foro_t; // posizione

typedef struct
{
    int other_xy;
    bool orentation;// /=true \=false
} specchio;

vector <vector <specchio> > specchi_x;
vector <vector <specchio> > specchi_y;
int x_max, y_max, result[3];

void inizia(int N, int M)
{
    specchi_x.resize(N);
    specchi_y.resize(M);
    x_max = N;
    y_max = M;
}

void aggiungi(int r, int c, char diagonale)
{
    specchio temp;
    temp.other_xy = c;
    temp.orentation = diagonale == '/';
    specchi_x[r].push_back(temp);

    temp.other_xy = r;
    specchi_y[c].push_back(temp);
}

int * final_position(int x, int y, int orientation)
{
    int min_other, pos;
    switch (orientation)
    {
    case 0: //SOPRA = 0,
        min_other = -1;
        pos;
        for(int i = 0; i < specchi_y[y].size(); ++i)
        {
            if(specchi_y[y][i].other_xy < x && specchi_y[y][i].other_xy > min_other)
            {
                min_other = specchi_y[y][i].other_xy;
                pos = i;
            }
        }
        if (min_other == -1)
        {
            if (specchi_y[y][pos].orentation)   // /
                return final_position(specchi_y[y][pos].other_xy, y, 1);
            else
                return final_position(specchi_y[y][pos].other_xy, y, 3);
        }
        break;
    case 1: // DESTRA = 1
        min_other = y_max;
        pos;
        for(int i = 0; i < specchi_x[x].size(); ++i)
        {
            if(specchi_y[y][i].other_xy > y && specchi_x[x][i].other_xy < min_other)
            {
                min_other = specchi_x[x][i].other_xy;
                pos = i;
            }
        }
        if (min_other == -1)
        {
            if (specchi_y[y][pos].orentation)   // /
                return final_position(x, specchi_y[y][pos].other_xy, 0);
            else
                return final_position(x, specchi_y[y][pos].other_xy, 2);
        }
        break;
    case 2: // SOTTO = 2
        min_other = x_max;
        pos;
        for(int i = 0; i < specchi_y[y].size(); ++i)
        {
            if(specchi_y[y][i].other_xy > x && specchi_y[y][i].other_xy < min_other)
            {
                min_other = specchi_y[y][i].other_xy;
                pos = i;
            }
        }
        if (min_other == -1)
        {
            if (specchi_y[y][pos].orentation)   // /
                return final_position(specchi_y[y][pos].other_xy, y, 3);
            else
                return final_position(specchi_y[y][pos].other_xy, y, 1);
        }
        break;
    case 3: // SINISTRA = 3
        min_other = -1;
        pos;
        for(int i = 0; i < specchi_x[x].size(); ++i)
        {
            if(specchi_y[y][i].other_xy < y && specchi_x[x][i].other_xy > min_other)
            {
                min_other = specchi_x[x][i].other_xy;
                pos = i;
            }
        }
        if (min_other == -1)
        {
            if (specchi_y[y][pos].orentation)   // /
                return final_position(x, specchi_y[y][pos].other_xy, 2);
            else
                return final_position(x, specchi_y[y][pos].other_xy, 0);
        }
        break;
    }

    switch (orientation)
    {
    case 0: //SOPRA = 0,
        result[0] = 0;
        result[1] = y;
        result[2] = 0;
        break;
    case 1: // DESTRA = 1
        result[0] = x;
        result[1] = y_max - 1;
        result[2] = 1;
        break;
    case 2: // SOTTO = 2
        result[0] = x_max - 1;
        result[1] = y;
        result[2] = 2;
        break;
    case 3: // SINISTRA = 3
        result[0] = x;
        result[1] = 0;
        result[2] = 3;
        break;
    }

    return result;
}

foro_t calcola(foro_t ingresso)
{
    int my_x, my_y, my_orientation;
    switch (ingresso.posizione)
    {
    case 0: //SOPRA = 0,
        my_orientation = 2;
        my_x = 0;
        my_y = ingresso.posizione;
        break;
    case 1: // DESTRA = 1
        my_orientation = 3;
        my_x = ingresso.posizione;
        my_y = y_max - 1;
        break;
    case 2: // SOTTO = 2
        my_orientation = 0;
        my_x = x_max - 1;
        my_y = ingresso.posizione;
        break;
    case 3: // SINISTRA = 3
        my_orientation = 1;
        my_x = ingresso.posizione;
        my_y = 0;
        break;
    }

    int *exit_points = final_position(my_x, my_y, my_orientation);

    // calcola il punto di uscita del raggio
    foro_t uscita;
    switch (exit_points[2])
    {
    case 0: //SOPRA = 0,
        uscita.lato = SOPRA;
        uscita.posizione = exit_points[1];
        break;
    case 1: // DESTRA = 1
        uscita.lato = DESTRA;
        uscita.posizione = exit_points[0];
        break;
    case 2: // SOTTO = 2
        uscita.lato = SOTTO;
        uscita.posizione = exit_points[1];
        break;
    case 3: // SINISTRA = 3
        uscita.lato = SINISTRA;
        uscita.posizione = exit_points[0];
        break;
    }
    return uscita;
}
