CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backward_moves --fwd_history_len=1 --bwd_history_len=0

psvn2c_core.c:
	cp ../../src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../../src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../../src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	echo "**** Constructing $@ ..."
	../../../bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

%.distSummary: %.c ../../../global/distSummary.cpp
	echo "**** Constructing $@ ..."
	$(CXX) $(OPT) ../../../global/distSummary.cpp -include $< -o $@
	rm -f $*.c

abstractor:
	echo "**** Constructing abstractor ..."
	$(CXX) $(OPT) ../../src/abstractor.cpp ../../src/psvn.cpp -o $@

%.pdb: abstractor
	rm -f `basename $*`.abst `basename $*`.pdb `basename $*`.psvn
	echo "**** Running abstractor on `dirname $*`.psvn with `basename $*`.txt ..."
	./abstractor `dirname $*`.psvn `basename $*` < `basename $*`.txt > /dev/null
	make `basename $*`.distSummary
	echo "**** Constructing PDB `basename $*`.pdb ..."
	./`basename $*`.distSummary `basename $*`.pdb
	rm -f abstractor `basename $*`.distSummary
	
%.ida : %.c ../../global/idaEstrella.cpp priority_queue.hpp node.hpp
	$(CXX) $(OPT) ../../global/idaEstrella.cpp -include $< -include 24-puzzle_pdb.cpp -o $@


%.a : %.c ../../global/aEstrella.cpp priority_queue.hpp node.hpp
	$(CXX) $(OPT) ../../global/aEstrella.cpp -include $< -include 24-puzzle_pdb.cpp -o $@

install: psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c

all: 
	make 24-puzzle/abs_24_1.pdb
	make 24-puzzle/abs_24_2.pdb
	make 24-puzzle/abs_24_3.pdb
	make 24-puzzle/abs_24_4.pdb
