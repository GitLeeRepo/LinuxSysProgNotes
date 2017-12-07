# Simple make for compiling individual C files into individual executables of 
# the same name. Intended for compiling simple demo/concept programs with 
# multiple executables in same directory This relies on implicit variables 
# and default actions to do the compile of the ${EXE} target. The implicit CC 
# and CFLAGS are redefined here, while RM uses the default 'rm -f'. Only 
# recompiles the specified files and header if they have changed since last 
# compile

EXE = writepipe readpipe
INCFILES = pipe.h
LDLIBS = ~/source/c/commonlib/common.o
CC=gcc
CFLAGS = -gdwarf -Wall

.PHONY: info clean

all: info ${LDLIBS} ${EXE}

info:
	@echo "Info: make for: $(EXE)"

# compile happens here
${EXE}: $(INCFILES) 

# compile common object tile
${LDLIBS}: $(INCFILES) 

clean:
	$(RM) $(EXE) *.o
