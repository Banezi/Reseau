#SRC=Chaine.cpp tests_catch.cpp main_test.cpp
SRC=$(wildcard *.c)
EXE=executable
GXX=gcc

CXXFLAGS+=-Wall -Wextra -MMD -g -O2
LDFLAGS=

OBJ=$(addprefix build/,$(SRC:.c=.o))
DEP=$(addprefix build/,$(SRC:.c=.d))

all: $(OBJ)
	$(GXX) -o $(EXE) $^ $(LDFLAGS)

build/%.o: %.c
	@mkdir -p build
	$(GXX) $(CXXFLAGS) -o $@ -c $<

clean:
	rm -rf build core *.gch


-include $(DEP)


