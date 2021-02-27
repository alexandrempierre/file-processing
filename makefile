main: counting_seq.o single_value.o triplets.o
	gcc -o main.out counting_seq.o single_value.o triplets.o main.c -Wall --pedantic
triplets: triplets.c
	gcc -o triplets.o triplets.c -c -Wall --pedantic
single_value: single_value.c
	gcc -o single_value.o single_value.c -c -Wall --pedantic
counting_seq: counting_seq.c
	gcc -o counting_seq.o counting_seq.c -c -Wall --pedantic
clean:
	rm *.o *.out