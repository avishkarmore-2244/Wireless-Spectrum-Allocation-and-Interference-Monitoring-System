all:
	gcc sourcefile/*.c -o main -Iincludefile -lpthread

run:
	./main

clean:
	rm -f main log.txt

test:
	./main
