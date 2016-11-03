tachyon.o: 
	gcc tachyon.c -o tachyon.o

run: tachyon.o
	./tachyon.o

clean:
	rm *.o