// Include all necessary
#include <bits/stdc++.h>
using namespace std;

// My personal structures, helps me to get easier the infos
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
    bool orientation;// /=true \=false
} specchio;

vector <map <int, bool> > specchi_x; // other_xy, orientation
vector <map <int, bool> > specchi_y; // other_xy, orientation
vector <map <int, bool> > specchi_x2; // other_xy, orientation
vector <map <int, bool> > specchi_y2; // other_xy, orientation
int x_max, y_max, result[3];

void inizia(int N, int M)
{
    // Inizialize my variabiles
    specchi_x.resize(M);
    specchi_y.resize(N);
    specchi_x2.resize(M);
    specchi_y2.resize(N);
    x_max = M;
    y_max = N;
    // cout << N << "\t" << M << endl;
}

void aggiungi(int r, int c, char diagonale)
{
    // Add my new "specchio" into specchi_y array with x as other_xy and into specchi_x array with y as other_xy
    specchi_x[c][r] = diagonale == '/';
    specchi_y[r][c] = diagonale == '/';
    specchi_x2[c].insert({-r, diagonale == '/'});
    specchi_y2[r].insert({-c, diagonale == '/'});
}

int * final_position(int x, int y, int orientation, bool just_go)
{
    // cout << "My actual position: " << x << "\t" << y << "\t" << orientation << "\t" << just_go << endl;

    // Search next "specchio" and if it's go to next position and repeat searching (recursive)
    int min_other, pos;
    switch (orientation)
    {
    case 0: //SOPRA = 0
        if (!just_go && specchi_x[x].find(y) != specchi_x[x].end())
        {
            if (specchi_x[x].find(y)->second)   // /
                return final_position(x, y, 1, true);
            else
                return final_position(x, y, 3, true);
        }
        else
        {
            auto it = specchi_x2[x].upper_bound(-y);
            if (it != specchi_x2[x].end())
            {
                if (it->second)   // /
                    return final_position(x, -(it->first), 1, true);
                else
                    return final_position(x, -(it->first), 3, true);
            }
        }
        break;
    case 1: // DESTRA = 1
        if (!just_go && specchi_y[y].find(x) != specchi_y[y].end())
        {
            if (specchi_y[y].find(x)->second)   // /
                return final_position(x, y, 0, true);
            else
                return final_position(x, y, 2, true);
        }
        else
        {
            auto it = specchi_y[y].upper_bound(x);
            if (it != specchi_y[y].end())
            {
                if (it->second)   // /
                    return final_position(it->first, y, 0, true);
                else
                    return final_position(it->first, y, 2, true);
            }
        }
        break;
    case 2: // SOTTO = 2
        if (!just_go && specchi_x[x].find(y) != specchi_x[x].end())
        {
            if (specchi_x[x].find(y)->second)   // /
                return final_position(x, y, 3, true);
            else
                return final_position(x, y, 1, true);
        }
        else
        {
            auto it = specchi_x[x].upper_bound(y);
            if (it != specchi_x[x].end())
            {
                if (it->second)   // /
                    return final_position(x, it->first, 3, true);
                else
                    return final_position(x, it->first, 1, true);
            }
        }
        break;
    case 3: // SINISTRA = 3
        if (!just_go && specchi_y[y].find(x) != specchi_y[y].end())
        {
            if (specchi_y[y].find(x)->second)   // /
                return final_position(x, y, 2, true);
            else
                return final_position(x, y, 0, true);
        }
        else
        {
            auto it = specchi_y2[y].upper_bound(-x);
            if (it != specchi_y2[y].end())
            {
                if (it->second)   // /
                    return final_position(-(it->first), y, 2, true);
                else
                    return final_position(-(it->first), y, 0, true);
            }
        }
        break;
    }

    // Get end position
    switch (orientation)
    {
    case 0: //SOPRA = 0
        result[0] = x;
        result[1] = 0;
        result[2] = 0;
        break;
    case 1: // DESTRA = 1
        result[0] = x_max - 1;
        result[1] = y;
        result[2] = 1;
        break;
    case 2: // SOTTO = 2
        result[2] = 2;
        result[0] = x;
        result[1] = y_max - 1;
        break;
    case 3: // SINISTRA = 3
        result[0] = 0;
        result[1] = y;
        result[2] = 3;
        break;
    }

    return result;
}

foro_t calcola(foro_t ingresso)
{
    // cout << "NEW TEST: " << ingresso.posizione << " " << ingresso.lato << endl;

    // Convert by posizione & lato to x, y, orientamento
    int my_x, my_y, my_orientation;
    switch (ingresso.lato)
    {
    case 0: //SOPRA = 0
        my_orientation = 2;
        my_x = ingresso.posizione;
        my_y = 0;
        break;
    case 1: // DESTRA = 1
        my_orientation = 3;
        my_x = x_max - 1;
        my_y = ingresso.posizione;
        break;
    case 2: // SOTTO = 2
        my_orientation = 0;
        my_x = ingresso.posizione;
        my_y = y_max - 1;
        break;
    case 3: // SINISTRA = 3
        my_orientation = 1;
        my_x = 0;
        my_y = ingresso.posizione;
        break;
    }

    // Core
    int *exit_points = final_position(my_x, my_y, my_orientation, false);

    // Convert by x, y, orientamento to posizione & lato
    foro_t uscita;
    switch (exit_points[2])
    {
    case 0: //SOPRA = 0
        uscita.lato = SOPRA;
        uscita.posizione = exit_points[0];
        break;
    case 1: // DESTRA = 1
        uscita.lato = DESTRA;
        uscita.posizione = exit_points[1];
        break;
    case 2: // SOTTO = 2
        uscita.lato = SOTTO;
        uscita.posizione = exit_points[0];
        break;
    case 3: // SINISTRA = 3
        uscita.lato = SINISTRA;
        uscita.posizione = exit_points[1];
        break;
    }

    // End
    return uscita;
}











/* EXAMPLE CASES
 */

//4 5 5 / 1 2 \ 1 4 ? 1 1 / 3 4 ? 2 2
/*
0 4
3 3
*/

//6 2 7 ? 1 1 / 1 1 \ 4 0 / 4 1 / 1 0 ? 0 1 ? 1 1
/*
3 1
1 1
0 1
*/







/* BASE PART
 * DON'T CHANGE IT
 */
#include <stdio.h>
#include <assert.h>

void inizia(int N, int M);
void aggiungi(int riga, int colonna, char orientamento);
foro_t calcola(foro_t ingresso);

int main()
{
    int N, M, Q, riga, colonna, lato, posizione, i;
    char tipo;

    assert(3 == scanf("%d %d %d", &N, &M, &Q));
    inizia(N, M);

    for (i = 0; i < Q; i++)
    {
        assert(1 == scanf(" %c", &tipo));
        if (tipo == '?')
        {
            assert(2 == scanf("%d %d", &lato, &posizione));
            foro_t in = {(parete_t)lato, posizione};
            foro_t res = calcola(in);
            printf("%d %d\n", res.lato, res.posizione);
        }
        else if (tipo == '/' || tipo == '\\')
        {
            assert(2 == scanf("%d %d", &riga, &colonna));
            aggiungi(riga, colonna, tipo);
        }
        else
        {
            fprintf(stderr, "Tipo di comando errato (validi: / \\ ?): %c (ascii %d)\n", tipo, (int)tipo);
            assert(0);
        }
    }
}
