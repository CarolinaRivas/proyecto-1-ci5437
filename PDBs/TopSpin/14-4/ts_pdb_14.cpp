#include <iostream>

state_map_t *map1;
state_map_t *map2;
state_map_t *map3;
abstraction_t *abs1;
abstraction_t *abs2;
abstraction_t *abs3;
state_t abs_state1;
state_t abs_state2;
state_t abs_state3;
unsigned sum;

void cargarPDBs(){
	FILE *f1 = fopen("abs_ts_14_1.pdb","r");
	FILE *f2 = fopen("abs_ts_14_2.pdb","r");
	FILE *f3 = fopen("abs_ts_14_3.pdb","r");

	abs1 = read_abstraction_from_file("abs_ts_14_1.abst");
	map1 = read_state_map(f1);

	abs2 = read_abstraction_from_file("abs_ts_14_2.abst");
	map2 = read_state_map(f2);

	abs3 = read_abstraction_from_file("abs_ts_14_3.abst");
	map3 = read_state_map(f3);

	fclose(f1);
	fclose(f2);
	fclose(f3);	
}

unsigned heuristica(state_t puzzle_state){
	abstract_state(abs1, &puzzle_state, &abs_state1);
	abstract_state(abs2, &puzzle_state, &abs_state2);
	abstract_state(abs3, &puzzle_state, &abs_state3);
	
	if((*state_map_get(map1, &abs_state1) > *state_map_get(map2, &abs_state2))&& (*state_map_get(map1, &abs_state1)>*state_map_get(map3, &abs_state3))){
		sum = *state_map_get(map1, &abs_state1) ;
	}else if((*state_map_get(map2, &abs_state2)>*state_map_get(map1, &abs_state1)) && (*state_map_get(map2, &abs_state2)>*state_map_get(map3, &abs_state3))){
		sum = *state_map_get(map2, &abs_state2);
	}else if((*state_map_get(map3, &abs_state3)>*state_map_get(map1, &abs_state1)) && (*state_map_get(map3, &abs_state3)>*state_map_get(map2, &abs_state2))){
		sum = *state_map_get(map3, &abs_state3);
	}

	return (sum);
}