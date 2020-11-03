// Include all necessary
#include <bits/stdc++.h>
using namespace std;

// #define DEBUG    // enable debug prints

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
    int x;
    int y;
    int orientation;
} position;

typedef struct
{
    position up;
    position right;
    position down;
    position left;
    position up_j;
    position right_j;
    position down_j;
    position left_j;
    char mirrow;
} specchio;

vector <map <int, specchio> > specchi_x;  // other_xy, specchio
vector <map <int, specchio> > specchi_y;  // other_xy, specchio
vector <map <int, specchio> > specchi_x2; // other_xy, specchio
vector <map <int, specchio> > specchi_y2; // other_xy, specchio
int x_max, y_max, result[3];

vector <pair <foro_t, foro_t> > last_results;

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
    # ifdef DEBUG
    cout << "Add: " << c << " " << r << " " << diagonale << endl; // debug
    #endif // DEBUG

    // Reset my last results
    last_results.clear();

    // Add my new "specchio" into specchi_y array with x as other_xy and into specchi_x array with y as other_xy
    specchio my_new;

    // default values
    my_new.up.x = -1;
    my_new.right.x = -1;
    my_new.down.x = -1;
    my_new.left.x = -1;
    my_new.up_j.x = -1;
    my_new.right_j.x = -1;
    my_new.down_j.x = -1;
    my_new.left_j.x = -1;
    my_new.up.y = -1;
    my_new.right.y = -1;
    my_new.down.y = -1;
    my_new.left.y = -1;
    my_new.up_j.y = -1;
    my_new.right_j.y = -1;
    my_new.down_j.y = -1;
    my_new.left_j.y = -1;
    my_new.mirrow = diagonale;

    int x = c;
    int y = r;

    {
        #ifdef DEBUG
        cout << 1;
        #endif // DEBUG
        auto it = specchi_x2[x].upper_bound(-y);
        if (it != specchi_x2[x].end())
        {
            if (diagonale == '/')    // /
            {
                my_new.up.x = x;
                my_new.up.y = -(it->first);
                my_new.up.orientation = 1;
                my_new.up_j.x = x;
                my_new.up_j.y = -(it->first);
                my_new.up_j.orientation = 1;
            }
            else
            {
                my_new.up.x = x;
                my_new.up.y = -(it->first);
                my_new.up.orientation = 3;
                my_new.up_j.x = x;
                my_new.up_j.y = -(it->first);
                my_new.up_j.orientation = 3;
            }
        }

        auto it2 = specchi_x2[x].upper_bound(-y);
        if (it != it2)
        {
            if (diagonale == '/')    // /
            {
                my_new.up_j.x = x;
                my_new.up_j.y = y;
                my_new.up_j.orientation = 1;

            }
            else
            {
                my_new.up_j.x = x;
                my_new.up_j.y = y;
                my_new.up_j.orientation = 3;
            }
        }
    }


    {
        #ifdef DEBUG
        cout << 2;
        #endif // DEBUG
        auto it = specchi_y[y].upper_bound(x);
        if (it != specchi_y[y].end())
        {
            if (diagonale == '/')    // /
            {
                my_new.right.x = it->first;
                my_new.right.y = y;
                my_new.right.orientation = 0;
                my_new.right_j.x = it->first;
                my_new.right_j.y = y;
                my_new.right_j.orientation = 0;
            }
            else
            {
                my_new.right.x = it->first;
                my_new.right.y = y;
                my_new.right.orientation = 2;
                my_new.right_j.x = it->first;
                my_new.right_j.y = y;
                my_new.right_j.orientation = 2;
            }
        }

        auto it2 = specchi_x2[x].upper_bound(-y);
        if (it != it2)
        {
            if (diagonale == '/')    // /
            {
                my_new.right_j.x = x;
                my_new.right_j.y = y;
                my_new.right_j.orientation = 0;

            }
            else
            {
                my_new.right_j.x = x;
                my_new.right_j.y = y;
                my_new.right_j.orientation = 2;
            }
        }
    }


    {
        #ifdef DEBUG
        cout << 3;
        #endif // DEBUG
        auto it = specchi_x[x].upper_bound(y);
        if (it != specchi_x[x].end())
        {
            if (diagonale == '/')    // /
            {
                my_new.down.x = x;
                my_new.down.y = it->first;
                my_new.down.orientation = 3;
                my_new.down_j.x = x;
                my_new.down_j.y = it->first;
                my_new.down_j.orientation = 3;
            }
            else
            {
                my_new.down.x = x;
                my_new.down.y = it->first;
                my_new.down.orientation = 1;
                my_new.down_j.x = x;
                my_new.down_j.y = it->first;
                my_new.down_j.orientation = 1;
            }
        }

        auto it2 = specchi_x2[x].upper_bound(-y);
        if (it != it2)
        {
            if (diagonale == '/')    // /
            {
                my_new.down_j.x = x;
                my_new.down_j.y = y;
                my_new.down_j.orientation = 3;

            }
            else
            {
                my_new.down_j.x = x;
                my_new.down_j.y = y;
                my_new.down_j.orientation = 1;
            }
        }
    }



    {
        #ifdef DEBUG
        cout << 4;
        #endif // DEBUG
        auto it = specchi_y2[y].upper_bound(-x);
        if (it != specchi_y2[y].end())
        {
            if (diagonale == '/')    // /
            {
                my_new.left.x = -(it->first);
                my_new.left.y = y;
                my_new.left.orientation = 2;
                my_new.left_j.x = -(it->first);
                my_new.left_j.y = y;
                my_new.left_j.orientation = 2;
            }
            else
            {
                my_new.left.x = -(it->first);
                my_new.left.y = y;
                my_new.left.orientation = 0;
                my_new.left_j.x = -(it->first);
                my_new.left_j.y = y;
                my_new.left_j.orientation = 0;
            }
        }

        auto it2 = specchi_x2[x].upper_bound(-y);
        if (it != it2)
        {
            if (diagonale == '/')    // /
            {
                my_new.left_j.x = x;
                my_new.left_j.y = y;
                my_new.left_j.orientation = 2;

            }
            else
            {
                my_new.left_j.x = x;
                my_new.left_j.y = y;
                my_new.left_j.orientation = 0;
            }
        }
    }
    #ifdef DEBUG
    cout << 5;
    #endif // DEBUG
    if (my_new.up.x != -1)
    {
        auto it = specchi_x[my_new.up.x].find(my_new.up.y);
        if (it != specchi_x[my_new.up.x].end())
        {
            it->second.down.x = x;
            it->second.down.y = y;
        }

        it = specchi_x2[my_new.up.x].find(-my_new.up.y);
        if (it != specchi_x2[my_new.up.x].end())
        {
            it->second.down.x = x;
            it->second.down.y = y;
        }

        it = specchi_y[my_new.up.y].find(my_new.up.x);
        if (it != specchi_y[my_new.up.y].end())
        {
            it->second.down.x = x;
            it->second.down.y = y;
        }

        it = specchi_y2[my_new.up.y].find(-my_new.up.x);
        if (it != specchi_y2[my_new.up.y].end())
        {
            it->second.down.x = x;
            it->second.down.y = y;
        }
    }
    if (my_new.right.x != -1)
    {
        auto it = specchi_x[my_new.right.x].find(my_new.right.y);
        if (it != specchi_x[my_new.right.x].end())
        {
            it->second.left.x = x;
            it->second.left.y = y;
        }

        it = specchi_x2[my_new.right.x].find(-my_new.right.y);
        if (it != specchi_x2[my_new.right.x].end())
        {
            it->second.left.x = x;
            it->second.left.y = y;
        }

        it = specchi_y[my_new.right.y].find(my_new.right.x);
        if (it != specchi_y[my_new.right.y].end())
        {
            it->second.left.x = x;
            it->second.left.y = y;
        }

        it = specchi_y2[my_new.right.y].find(-my_new.right.x);
        if (it != specchi_y2[my_new.right.y].end())
        {
            it->second.left.x = x;
            it->second.left.y = y;
        }
    }
    if (my_new.down.x != -1)
    {
        auto it = specchi_x[my_new.down.x].find(my_new.down.y);
        if (it != specchi_x[my_new.down.x].end())
        {
            it->second.up.x = x;
            it->second.up.y = y;
        }

        it = specchi_x2[my_new.down.x].find(-my_new.down.y);
        if (it != specchi_x2[my_new.down.x].end())
        {
            it->second.up.x = x;
            it->second.up.y = y;
        }

        it = specchi_y[my_new.down.y].find(my_new.down.x);
        if (it != specchi_y[my_new.down.y].end())
        {
            it->second.up.x = x;
            it->second.up.y = y;
        }

        it = specchi_y2[my_new.down.y].find(-my_new.down.x);
        if (it != specchi_y2[my_new.down.y].end())
        {
            it->second.up.x = x;
            it->second.up.y = y;
        }
    }
    if (my_new.left.x != -1)
    {
        auto it = specchi_x[my_new.left.x].find(my_new.left.y);
        if (it != specchi_x[my_new.left.x].end())
        {
            it->second.right.x = x;
            it->second.right.y = y;
        }

        it = specchi_x2[my_new.left.x].find(-my_new.left.y);
        if (it != specchi_x2[my_new.left.x].end())
        {
            it->second.right.x = x;
            it->second.right.y = y;
        }

        it = specchi_y[my_new.left.y].find(my_new.left.x);
        if (it != specchi_y[my_new.left.y].end())
        {
            it->second.right.x = x;
            it->second.right.y = y;
        }

        it = specchi_y2[my_new.left.y].find(-my_new.left.x);
        if (it != specchi_y2[my_new.left.y].end())
        {
            it->second.right.x = x;
            it->second.right.y = y;
        }
    }

    #ifdef DEBUG
    cout << 6;
    #endif // DEBUG
    specchi_x[c].insert({r, my_new});
    specchi_x2[c].insert({-r, my_new});
    specchi_y[r].insert({c, my_new});
    specchi_y2[r].insert({-c, my_new});

    #ifdef DEBUG
    cout << 7 << endl;
    for (int i = 0; i < specchi_x.size(); ++i)
    {
        for (auto const& element : specchi_x[i])
        {
            cout << "My 'specchio (x)' -> x: " << i << "\t y: " << element.first << "\tup: (" << element.second.up.x << ", " << element.second.up.y << ")" << "\trigth: (" << element.second.right.x << ", " << element.second.right.y << ")" << "\tdown: (" << element.second.down.x << ", " << element.second.down.y << ")" << "\tleft: (" << element.second.left.x << ", " << element.second.left.y << ")" << endl ;
        }
    }
    for (int i = 0; i < specchi_x2.size(); ++i)
    {
        for (auto const& element : specchi_x2[i])
        {
            cout << "My 'specchio (x2)' -> x: " << i << "\t y: " << element.first << "\tup: (" << element.second.up.x << ", " << element.second.up.y << ")" << "\trigth: (" << element.second.right.x << ", " << element.second.right.y << ")" << "\tdown: (" << element.second.down.x << ", " << element.second.down.y << ")" << "\tleft: (" << element.second.left.x << ", " << element.second.left.y << ")" << endl ;
        }
    }
    for (int i = 0; i < specchi_y.size(); ++i)
    {
        for (auto const& element : specchi_y[i])
        {
            cout << "My 'specchio (y)' -> x: " << element.first << "\t y: " << i << "\tup: (" << element.second.up.x << ", " << element.second.up.y << ")" << "\trigth: (" << element.second.right.x << ", " << element.second.right.y << ")" << "\tdown: (" << element.second.down.x << ", " << element.second.down.y << ")" << "\tleft: (" << element.second.left.x << ", " << element.second.left.y << ")" << endl ;
        }
    }
    for (int i = 0; i < specchi_y2.size(); ++i)
    {
        for (auto const& element : specchi_y2[i])
        {
            cout << "My 'specchio (y2)' -> x: " << element.first << "\t y: " << i << "\tup: (" << element.second.up.x << ", " << element.second.up.y << ")" << "\trigth: (" << element.second.right.x << ", " << element.second.right.y << ")" << "\tdown: (" << element.second.down.x << ", " << element.second.down.y << ")" << "\tleft: (" << element.second.left.x << ", " << element.second.left.y << ")" << endl ;
        }
    }
    #endif // DEBUG
}

#ifdef DEBUG
int counter = 0;
#endif // DEBUG

int * final_position(int x, int y, int orientation, bool just_go)
{
    #ifdef DEBUG
    cout << "My actual position: " << x << "\t" << y << "\t" << orientation << "\t" << just_go << "\t" << specchi_x[x].find(y)->second.mirrow<< endl;
    if (++counter == 15)
    {
        while (true)
        {
            NULL;
        }
    }
    #endif // DEBUG
    // Search next "specchio" and if it's go to next position and repeat searching (recursive)
    switch (orientation)
    {
    case 0: //SOPRA = 0
        if (!just_go)
        {
            auto first_time = specchi_x2[x].lower_bound(-y);
            if (first_time != specchi_x2[x].end())
            {
                if(first_time->second.mirrow == '/')
                    return final_position(x, -(first_time->first), 1, true);
                else
                    return final_position(x, -(first_time->first), 3, true);
            }
        }

        else if (specchi_x2[x][-y].up.x != -1)
        {
            if (specchi_x[specchi_x2[x][-y].up.x][specchi_x2[x][-y].up.y].mirrow == '/')
                return final_position(specchi_x2[x][-y].up.x, specchi_x2[x][-y].up.y, 1, true);
            else
                return final_position(specchi_x2[x][-y].up.x, specchi_x2[x][-y].up.y, 3, true);
        }
        break;

    case 1: // DESTRA = 1
        if (!just_go)
        {
            auto first_time = specchi_y[y].lower_bound(x);
            if (first_time != specchi_y[y].end())
            {
                if(first_time->second.mirrow == '/')
                    return final_position(first_time->first, y, 0, true);
                else
                    return final_position(first_time->first, y, 2, true);
            }
        }

        else if (specchi_y[y][x].right.x != -1)
        {
            if (specchi_x[specchi_y[y][x].right.x][specchi_y[y][x].right.y].mirrow == '/')
                return final_position(specchi_y[y][x].right.x, specchi_y[y][x].right.y, 0, true);
            else
                return final_position(specchi_y[y][x].right.x, specchi_y[y][x].right.y, 2, true);
        }

        break;
    case 2: // SOTTO = 2
        if (!just_go)
        {
            auto first_time = specchi_x[x].lower_bound(y);
            if (first_time != specchi_x[x].end())
            {
                if(first_time->second.mirrow == '/')
                    return final_position(x, first_time->first, 3, true);
                else
                    return final_position(x, first_time->first, 1, true);
            }
        }

        else if (specchi_x[x][y].down.x != -1)
        {
            if (specchi_x[specchi_x[x][y].down.x][specchi_x[x][y].down.y].mirrow == '/')
                return final_position(specchi_x[x][y].down.x, specchi_x[x][y].down.y, 3, true);
            else
                return final_position(specchi_x[x][y].down.x, specchi_x[x][y].down.y, 1, true);
        }

        break;

    case 3: // SINISTRA = 3
        if (!just_go)
        {
            auto first_time = specchi_y2[y].lower_bound(-x);
            if (first_time != specchi_y2[y].end())
            {
                if(first_time->second.mirrow == '/')
                    return final_position(-(first_time->first), y, 2, true);
                else
                    return final_position(-(first_time->first), y, 0, true);
            }
        }

        else if (specchi_y2[y][-x].left.x != -1)
        {
            if (specchi_x[specchi_y2[y][-x].left.x][specchi_y2[y][-x].left.y].mirrow == '/')
                return final_position(specchi_y2[y][-x].left.x, specchi_y2[y][-x].left.y, 2, true);
            else
                return final_position(specchi_y2[y][-x].left.x, specchi_y2[y][-x].left.y, 0, true);

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
        result[0] = x;
        result[1] = y_max - 1;
        result[2] = 2;
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
    for (int i  = 0; i < last_results.size(); ++i)
    {
        if(last_results[i].first.lato == ingresso.lato && last_results[i].first.posizione == ingresso.posizione)
            return last_results[i].second;
    }
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

    last_results.push_back(make_pair(ingresso, uscita));

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
