all: obj/bloqueled.o  obj/test.o exe

obj/test.o:
	g++ -c src/test.cpp -o obj/test.o -Iinclude

obj/bloqueled.o:
	g++ -c src/bloqueled.cpp -o obj/bloqueled.o -Iinclude

library:
	ar rvs lib/libLeds.a obj/bloqueLed.o

exe:
	g++ obj/bloqueled.o obj/test.o -o bin/bloqueled -Iinclude

clean:
	@echo "Cleaning"
	rm obj/*
	rm lib/*
	rm bin/*
