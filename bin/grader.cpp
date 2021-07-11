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
    bool orentation;// /=true \=false
} specchio;

vector <vector <specchio> > specchi_x;
vector <vector <specchio> > specchi_y;
int x_max, y_max, result[3];

void inizia(int N, int M)
{
    // Inizialize my variabiles
    specchi_x.resize(M);
    specchi_y.resize(N);
    x_max = M;
    y_max = N;
    // cout << N << "\t" << M << endl;
}

void aggiungi(int r, int c, char diagonale)
{
    // Add my new "specchio" into specchi_y array with x as other_xy and into specchi_x array with y as other_xy
    specchio temp;
    temp.other_xy = c;
    temp.orentation = diagonale == '/';
    specchi_y[r].push_back(temp);

    temp.other_xy = r;
    specchi_x[c].push_back(temp);

    /* // Check existent "specchi"
    cout << endl;
    for(int i = 0; i < specchi_x.size(); ++i)
    {
        for(int j = 0; j < specchi_x[i].size(); ++j)
            cout << i << "\t" << specchi_x[i][j].other_xy << "\t" << specchi_x[i][j].orentation << endl;
    }*/
}

int * final_position(int x, int y, int orientation, bool just_go)
{
    // cout << "My actual position: " << x << "\t" << y << "\t" << orientation << "\t" << just_go << endl;

    // Search next "specchio" and if it's go to next position and repeat searching (recursive)
    int min_other, pos;
    switch (orientation)
    {
    case 0: //SOPRA = 0
        min_other = -1;
        for(int i = 0; i < specchi_x[x].size(); ++i)
        {
            if(((specchi_x[x][i].other_xy < y && just_go) || (specchi_x[x][i].other_xy <= y && !just_go)) && specchi_x[x][i].other_xy > min_other)
            {
                min_other = specchi_x[x][i].other_xy;
                pos = i;
            }
        }
        if (min_other != -1)
        {
            if (specchi_x[x][pos].orentation)   // /
                return final_position(x, specchi_x[x][pos].other_xy, 1, true);
            else
                return final_position(x, specchi_x[x][pos].other_xy, 3, true);
        }
        break;
    case 1: // DESTRA = 1
        min_other = x_max;
        for(int i = 0; i < specchi_y[y].size(); ++i)
        {
            if(((specchi_y[y][i].other_xy > x && just_go) || (specchi_y[y][i].other_xy >= x && !just_go))&& specchi_y[y][i].other_xy < min_other)
            {
                min_other = specchi_y[y][i].other_xy;
                pos = i;
            }
        }
        if (min_other != x_max)
        {
            if (specchi_y[y][pos].orentation)   // /
                return final_position(specchi_y[y][pos].other_xy, y, 0, true);
            else
                return final_position(specchi_y[y][pos].other_xy, y, 2, true);
        }
        break;
    case 2: // SOTTO = 2
        min_other = y_max;
        for(int i = 0; i < specchi_x[x].size(); ++i)
        {
            if(((specchi_x[x][i].other_xy > y && just_go) || (specchi_x[x][i].other_xy >= y && !just_go)) && specchi_x[x][i].other_xy < min_other)
            {
                min_other = specchi_x[x][i].other_xy;
                pos = i;
            }
        }
        if (min_other != y_max)
        {
            if (specchi_x[x][pos].orentation)   // /
                return final_position(x, specchi_x[x][pos].other_xy, 3, true);
            else
                return final_position(x, specchi_x[x][pos].other_xy, 1, true);
        }
        break;
    case 3: // SINISTRA = 3
        min_other = -1;
        for(int i = 0; i < specchi_y[y].size(); ++i)
        {
            if(((specchi_y[y][i].other_xy < x && just_go) || (specchi_y[y][i].other_xy <= x && !just_go)) && specchi_y[y][i].other_xy > min_other)
            {
                min_other = specchi_y[y][i].other_xy;
                pos = i;
            }
        }
        if (min_other != -1)
        {
            if (specchi_y[y][pos].orentation)   // /
                return final_position(specchi_y[y][pos].other_xy, y, 2, true);
            else
                return final_position(specchi_y[y][pos].other_xy, y, 0, true);
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

int main() {
	int N, M, Q, riga, colonna, lato, posizione, i;
	char tipo;

	assert(3 == scanf("%d %d %d", &N, &M, &Q));
	inizia(N, M);

	for (i = 0; i < Q; i++) {
		assert(1 == scanf(" %c", &tipo));
		if (tipo == '?') {
			assert(2 == scanf("%d %d", &lato, &posizione));
			foro_t in = {(parete_t)lato, posizione};
			foro_t res = calcola(in);
			printf("%d %d\n", res.lato, res.posizione);
		} else if (tipo == '/' || tipo == '\\') {
			assert(2 == scanf("%d %d", &riga, &colonna));
			aggiungi(riga, colonna, tipo);
		} else {
			fprintf(stderr, "Tipo di comando errato (validi: / \\ ?): %c (ascii %d)\n", tipo, (int)tipo);
			assert(0);
		}
	}
}
