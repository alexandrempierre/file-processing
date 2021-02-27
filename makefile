INCLUDES=-Iincludes
OPTIONS=-Wall --pedantic

CC=gcc
CFLAGS=$(INCLUDES) $(OPTIONS)

main: counting_seq.o single_value.o triplets.o
	$(CC) -o main.out counting_seq.o single_value.o triplets.o main.c $(CFLAGS)

generate_input_file: counting_seq.o single_value.o triplets.o
	$(CC) -o generate_input_file.out counting_seq.o single_value.o triplets.o generate_input_file.c $(CFLAGS)

triplets: triplets.c
	$(CC) -o triplets.o triplets.c -c $(CFLAGS)

single_value: single_value.c
	$(CC) -o single_value.o single_value.c -c $(CFLAGS)

counting_seq: counting_seq.c
	$(CC) -o bin/counting_seq.o counting_seq.c $(CFLAGS)

clean:
	rm *.o *.out
