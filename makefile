OPTIONS=-Wall --pedantic -g

main: counting_seq.o single_value.o triplets.o
	gcc -o main.out counting_seq.o single_value.o triplets.o main.c $(OPTIONS)
generate_input_file: counting_seq.o single_value.o triplets.o
	gcc -o generate_input_file.out counting_seq.o single_value.o triplets.o generate_input_file.c $(OPTIONS)
triplets: triplets.c
	gcc -o triplets.o triplets.c -c $(OPTIONS)
single_value: single_value.c
	gcc -o single_value.o single_value.c -c $(OPTIONS)
counting_seq: counting_seq.c
	gcc -o counting_seq.o counting_seq.c -c $(OPTIONS)
clean:
	rm *.o *.out