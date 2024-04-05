
# Executable names:
EXE = mp_lists
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o

# Generated files
CLEAN_RM = actual-*.png

# Use the makefile template:
include make/template.mk
