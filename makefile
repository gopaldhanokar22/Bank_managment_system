out: main.o accounts.o transaction.o file_operations.o search.o
	cc main.o accounts.o transaction.o file_operations.o search.o -o out

main.o: main.c
	cc -c main.c

accounts.o: accounts.c
	cc -c accounts.c

transaction.o: transaction.c
	cc -c transaction.c

file_operations.o: file_operations.c
	cc -c file_operations.c

search.o: search.c
	cc -c search.c

clean:
	rm -f *.o out

