CC = gcc
CXX = g++
OPT = -Wall -O3 -Wno-unused-function -Wno-unused-variable
PSVNOPT = --state_map --backward_moves --fwd_history_len=0 --bwd_history_len=0

psvn2c_core.c:
	cp ../../psvn/src/psvn2c_core.c ./psvn2c_core.c

psvn2c_state_map.c:
	cp ../../psvn/src/psvn2c_state_map.c ./psvn2c_state_map.c

psvn2c_abstraction.c:
	cp ../../psvn/src/psvn2c_abstraction.c ./psvn2c_abstraction.c

%.c: %.psvn psvn2c_core.c psvn2c_state_map.c psvn2c_abstraction.c
	echo "**** Constructing $@ ..."
	../../psvn/bin/psvn2c $(PSVNOPT) --name=$(*F) < $< > $@
	rm -f ./psvn2c_core.c ./psvn2c_state_map.c ./psvn2c_abstraction.c

.PRECIOUS: %.c

priority_queue.hpp:
	cp ../../psvn/global/priority_queue.hpp ./priority_queue.hpp

node.hpp:
	cp ../../psvn/global/node.hpp ./node.hpp

%.distSummary: %.c ../../psvn/global/distSummary.cpp
	echo "**** Constructing $@ ..."
	$(CXX) $(OPT) ../../psvn/global/distSummary.cpp -include $< -o $@
	rm -f $*.c

abstractor:
	echo "**** Constructing abstractor ..."
	$(CXX) $(OPT) ../../psvn/src/abstractor.cpp ../../psvn/src/psvn.cpp -o $@

%.pdb: abstractor
	rm -f `basename $*`.abst `basename $*`.pdb `basename $*`.psvn
	echo "**** Running abstractor on `dirname $*`.psvn with `basename $*`.txt ..."
	./abstractor `dirname $*`.psvn `basename $*` < `basename $*`.txt > /dev/null
	make `basename $*`.distSummary
	echo "**** Constructing PDB `basename $*`.pdb ..."
	./`basename $*`.distSummary `basename $*`.pdb
	rm -f abstractor `basename $*`.distSummary

%.ida : %.c ../../psvn/global/idaEstrella.cpp priority_queue.hpp node.hpp
	$(CXX) $(OPT) ../../psvn/global/idaEstrella.cpp -include $< -include rubik_pdb.cpp -o $@


%.a : %.c ../../psvn/global/aEstrella.cpp priority_queue.hpp node.hpp
	$(CXX) $(OPT) ../../psvn/global/aEstrella.cpp -include $< -include rubik_pdb.cpp -o $@


generator.cc:
	cp ../../psvn/global/generator.cc ./generator.cc

%.generator: %.c generator.cc
	$(CXX) $(OPT) generator.cc -include $< -o $@
	rm -f ./generator.cc 
all : 
	make rubik3Stick/abs_1.pdb
	make rubik3Stick/abs_2.pdb
	make rubik3Stick/abs_3.pdb