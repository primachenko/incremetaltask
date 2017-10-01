all:
	gcc main.c types.h -o calc -lm
clean:
	rm calc