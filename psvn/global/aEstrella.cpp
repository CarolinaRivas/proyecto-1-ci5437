#include <vector>
#include "priority_queue.hpp"
#include <stdbool.h>
#include <fstream>
#include <string>
#include <time.h>
#define  MAX_LINE_LENGTH 999
using namespace std;
int64_t nodos;

int aEstrella(state_t *start)
{
    PriorityQueue<state_t> open;
    state_map_t *distance = new_state_map();
    state_t state, child; 
    int g, ruleid;
    ruleid_iterator_t iter;

    state_map_add( distance, start, 0 );
    open.Add(0, 0, *start );
    
    while(!open.Empty()) {
        g = open.CurrentPriority();
        state = open.Top();
        open.Pop();

        int *old_distance = state_map_get(distance, &state);
        ++nodos;

        if ((old_distance == NULL) || (g < *old_distance) || (!compare_states(&state, start))) {
            state_map_add( distance, &state, g );
            if (is_goal(&state)) {
                return g;
            }
            init_fwd_iter( &iter, &state );
            while( ( ruleid = next_ruleid( &iter ) ) >= 0 ) {
                apply_fwd_rule( ruleid, &state, &child );
                int child_g = g + get_fwd_rule_cost( ruleid );
                int child_h = heuristica(child);
                int child_f = child_g + child_h;
                if (child_h < INT_MAX) {
                    open.Add( child_f, child_g, child );

                }
            }
        }
    }
    return -1;
}

int main(int argc, char **argv){
    char str[MAX_LINE_LENGTH + 1];
    string line;
    int result;
    ssize_t numchars;
    float tiempoCorrida;
    state_t start;
    ifstream file;
    clock_t inicio, fin, duracion;


     cargarPDBs();


    printf("Ingrese el documento de puebas y presione Enter: ");
    if (fgets(str, sizeof str, stdin) == NULL) {
        printf("Error!.\n");
        return 0;
    }


    str[strlen(str)-1] = '\0';

    file.open(str);

    if (!file.is_open()) {
        printf("Error: nombre invalido: %s\n", str);
        return -1;
    }

    printf("Instancia \t\t\t Tiempo de solucion \t   Nodos expandidos       Distancia\t\n");
    printf("-----------------------------------------------------------------------------\n");
    
    while (!file.eof()) {
        getline(file, line);
        numchars = read_state(line.c_str(), &start);
        if (numchars <= 0) {
            printf("Error: invalid state entered.\n");
            //continue;
        }

        inicio = clock();
        nodos = 0; 
        result = aEstrella(&start);
        fin = clock();

        duracion = fin - inicio;

        tiempoCorrida = duracion / (double) CLOCKS_PER_SEC;

        if (result < 0) {
            printf("%s \t False \t %f \t %ld \t\t %d\n", line.c_str(), tiempoCorrida, nodos, result);
        } else {
            printf("%s \t True \t %f \t %ld \t\t %d\n", line.c_str(), tiempoCorrida, nodos, result);
        }
        
    }

    file.close();
    return 0;
}