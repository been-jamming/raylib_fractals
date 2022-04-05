LD_FLAGS = -lraylib -lm
OUTPUT = -o test

default:
	cc mobius.c test.c $(LD_FLAGS) $(OUTPUT)

clean:
	rm test
