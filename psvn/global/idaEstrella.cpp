#include <vector>
#include "priority_queue.hpp"
#include "node.hpp"
#include <stdbool.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <time.h>
#define  MAX_LINE_LENGTH 999
using namespace std;
int64_t nodos;

Node* f_bounded_dfs_visit(Node *n, unsigned bound, unsigned *nextBound, const int history) {
    unsigned f = (*n).g + heuristica((*n).state); 
    unsigned t = INT_MAX;
    int ruleid;
    int c_history;
    ruleid_iterator_t iter;
    state_t child;
    Node *next;

    if (f > bound) {
        *nextBound = f;
        return NULL;
    }

    if (is_goal(&(*n).state)) {
        *nextBound = (*n).g;
        return n;
    }

    ++nodos;

    init_fwd_iter(&iter, &(*n).state);
    while((ruleid = next_ruleid(&iter)) >= 0) {
        apply_fwd_rule(ruleid, &(*n).state, &child);

        if( !fwd_rule_valid_for_history( history, ruleid ) )
            continue;
        c_history = next_fwd_history( history, ruleid );

        Node n_child(child, n, ((*n).g + 1));

        next = f_bounded_dfs_visit(&n_child, bound, nextBound, c_history);

        if (next != NULL) {
            return next;
        }

        t = std::min(t, *nextBound);

    }

    *nextBound = t;
    return NULL;
}

Node ida_search(state_t *start){
    Node root(*start, NULL, 0);
    unsigned bound = heuristica(*start); 
    unsigned nextBound;
    Node *final;

    while(1){
       final = f_bounded_dfs_visit(&root, bound, &nextBound, init_history);

        if (final != NULL) {
            return *final;
        }
        bound = nextBound;
    }

}


int main(int argc, char **argv){
    char str[MAX_LINE_LENGTH + 1];
    string line;
    int d;
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
            continue;
        }

        inicio = clock();
        nodos = 0;
        Node goal = ida_search(&start);
        fin = clock();
        duracion = fin - inicio;
        tiempoCorrida = duracion / (double) CLOCKS_PER_SEC;
        printf("%s \t True \t %f \t %ld \t\t %d\n", line.c_str(), tiempoCorrida, nodos, goal.g);

    }
    file.close();
    return 0;
}





