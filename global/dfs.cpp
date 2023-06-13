#include <time.h>

int nodes[100];
int n_temp[100];
int tiempo;
time_t start, finish;
float temp;

void dfs(state_t state, int d, int bound, int history){
    state_t child;
    ruleid_iterator_t iter;
    int next_ruleid, next_child_hist;
    time(&finish);
    if ((difftime(finish,start)/60)>(float)tiempo) return;
    if (d>bound) return;
    
    init_fwd_iter(&iter, &state);
    next_ruleid = next_ruleid(&iter);
    while (next_ruleid >= 0){
        if(fwd_rule_valid_for_history(history,next_ruleid)){
            next_child_hist = next_fwd_history(history, next_ruleid);
            apply_fwd_rule(next_ruleid, &state, &child);
            dfs(child, d+1, bound, next_child_hist);
            nodes[d+1]++;
        }
        next_ruleid = next_ruleid(&iter);
    }
}

int main(int argc, char **argv){
    int bound;
    state_t state;
    if (argc < 2){
        printf("Cantidad de minutos no introducida porfvor corralo de la siguiente forma:\n");
        printf("~& ./<nombre del problema>.dfs <limite de minutos>\n");
        return 0;
    }
    

    time(&start);
    time(&finish);
    tiempo = atoi(argv[1]);
    if ((float)tiempo<=0){
        printf("La cantidad de minutos debe ser mayor a 0 (cero)\n");
        return 0;
    }
    bound = 0;
    
    while((temp = difftime(finish,start)/60)<(float)tiempo){

        for(int i=0; i<=bound;i++){
            nodes[i]=0;
        }
        nodes[0]=1;
        int d;
        first_goal_state(&state, &d);
        d = 0;
        int history = init_history;
        dfs(state, d, bound, history);
        bound++;
        time(&finish);
        if ((difftime(finish,start)/60)<(float)tiempo){
            for(int i=0; i<=bound;i++){
                n_temp[i]=nodes[i];
            }
        }
        
    }
    
    printf("Profundidad |\tNumero de nodos |\tFactor de ramificacion\n");
    for (int i=0; i<bound; i++){
        float branching_f = (float)n_temp[i] / (float)n_temp[i-1];
        printf("%d\t\t%d\t\t\t%f\n",i,n_temp[i],branching_f);
    }
    // printf("transcurrido %f minutos\n",temp);
    return 0;


}

