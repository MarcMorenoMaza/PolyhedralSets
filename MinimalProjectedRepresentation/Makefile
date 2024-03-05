
COMPILER_PRE_OPTIONS=-DGMPRATIONAL -DGNUMP
COMPILER_OPTIONS=-lpolylibgmp -lgmp -lm -O3 -flto -w -g
SRC1=inequality
SRC2=unrolledll
SRC3=set
SRC4=saturation
SRC5=projection
SRC6=fme
SRC7=bitarray

MAIN=main
CPLUS=g++

PERF = perf 
PERFO = stat -e cycles -e cache-misses -e instructions

all: prog

prog:
	$(CPLUS) $(COMPILER_PRE_OPTIONS) -Wall $(MAIN).cpp $(SRC1).cpp $(SRC2).cpp $(SRC3).cpp $(SRC4).cpp $(SRC5).cpp $(SRC6).cpp $(SRC7).c $(COMPILER_OPTIONS) -o MCS

change:
	g++ Change.cpp -lgmp -o Change

test: prog
	./MCS < test/32hedron

clean:
	rm -f MCS
	rm -f time.txt
	rm -f eachtime.txt
