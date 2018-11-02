# Simple make for compiling individual C files into individual executables of 
# the same name. Intended for compiling simple demo/concept programs with 
# multiple executables in same directory This relies on implicit variables 
# and default actions to do the compile of the $(OBJ) target. The implicit CC 
# and CFLAGS are redefined here, while RM uses the default 'rm -f'. Only 
# recompiles the specified files and header if they have changed since last 
# compile

OBJ = common.o
INCFILES =
LDLIBS =
CC=gcc
CFLAGS = -gdwarf -Wall

.PHONY: info clean

all: info $(LDLIBS) $(OBJ)

info:
	@echo "Info: make for: $(OBJ)"

# compile happens here
$(OBJ): $(INCFILES)

clean:
	$(RM) $(OBJ) *.o
