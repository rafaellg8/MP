all: obj/central.o library exe
	g++ obj/central.o obj/punto.o obj/circulo.o -o bin/central

obj/central.o:
	g++ -c src/central.cpp -o obj/central.o -Iinclude
	g++ -c src/punto.cpp -o obj/punto.o -Iinclude
	g++ -c src/circulo.cpp -o obj/circulo.o -Iinclude

library:
	ar rvs lib/libformas.a obj/punto.o obj/circulo.o

exe:
	g++ obj/central.o -lformas -o bin/central -Llib

clean:
	@echo "Cleaning"
	rm bin/*
	rm obj/*
	rm lib/*
