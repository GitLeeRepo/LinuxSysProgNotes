# Simple make for compiling individual C files into individual executables of the same name.
# It is not suitable (in its current form) for executables made up of multiple object files.
# Intended for compiling simple demo/concept programs
# This relies on implicit variables and default actions to do the compile of the ${EXE} target.
# The implicit CC and CFLAGS are redefined here, while RM uses the default 'rm -f'
# Only recompiles the specified files and header if they have changed since last compile

EXE = simplefork multiprog calledbyexec execprog execself forkexec
INCFILES =
CC=gcc
CFLAGS = -gdwarf -Wall

.PHONY: info clean

all: info ${EXE}

info:
	@echo "Info: make for: $(EXE)"

# compile happens here
${EXE}: $(INCFILES) 

clean:
	$(RM) $(EXE)
