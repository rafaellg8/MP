all: obj/central.o
	g++ obj/central.o obj/punto.o obj/circulo.o -o bin/central
obj/central.o:
	g++ -c src/central.cpp -o obj/central.o -Iinclude
	g++ -c src/punto.cpp -o obj/punto.o -Iinclude
	g++ -c src/circulo.cpp -o obj/circulo.o -Iinclude
clean:
	rm bin/*
	rm obj/*
