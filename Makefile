DEPS = cbuffer.h
OBJECT = cbuffer.o main.o 

INC_DIR := ./inc 
SRC_DIR := ./src

CFLAGS = $(foreach inc, $(INC_DIR), -I$(inc))
VPATH = $(foreach src, $(SRC_DIR), $(src))

*.o : *.c $(DEPS)
	gcc -c $< -o $@ $(CFLAGS)

all : $(OBJECT)
	gcc $(OBJECT) -o main.exe 

clean :
	rm -f *.o *.exe 