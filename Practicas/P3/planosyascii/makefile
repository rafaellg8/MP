
SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CPPFLAGS = -Wall -g -c -I$(INC)


all: $(BIN)/arteASCII $(BIN)/testarteASCII $(BIN)/testplano $(BIN)/testimagen

$(BIN)/arteASCII: $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/byte.o $(OBJ)/arteASCII.o
	$(CXX) $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/byte.o $(OBJ)/arteASCII.o -o $(BIN)/arteASCII
$(BIN)/testarteASCII: $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/testarteASCII.o $(OBJ)/byte.o
	$(CXX) $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/byte.o $(OBJ)/testarteASCII.o -o $(BIN)/testarteASCII

$(BIN)/testplano: $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/testplano.o $(OBJ)/byte.o
	$(CXX) $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/byte.o $(OBJ)/testplano.o -o $(BIN)/testplano

$(BIN)/testimagen: $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/testimagen.o $(OBJ)/byte.o
	$(CXX) $(OBJ)/imagen.o $(OBJ)/pgm.o $(OBJ)/testimagen.o $(OBJ)/byte.o -o $(BIN)/testimagen

# ************* CODIGOS OBJETO ******************* #
$(OBJ)/pgm.o:
	$(CXX) $(CPPFLAGS) $(SRC)/pgm.cpp -o $(OBJ)/pgm.o

$(OBJ)/imagen.o: $(OBJ)/byte.o
	$(CXX) $(CPPFLAGS) $(SRC)/imagen.cpp -o $(OBJ)/imagen.o

$(OBJ)/byte.o:
	$(CXX) $(CPPFLAGS) $(SRC)/byte.cpp -o $(OBJ)/byte.o

$(OBJ)/testimagen.o:
		$(CXX) $(CPPFLAGS) $(SRC)/testimagen.cpp -o $(OBJ)/testimagen.o

$(OBJ)/testplano.o:
		$(CXX) $(CPPFLAGS) $(SRC)/testplano.cpp -o $(OBJ)/testplano.o

$(OBJ)/testarteASCII.o:
		$(CXX) $(CPPFLAGS) $(SRC)/testarteASCII.cpp -o $(OBJ)/testarteASCII.o

$(OBJ)/arteASCII.o:
	$(CXX) $(CPPFLAGS) $(SRC)/arteASCII.cpp -o $(OBJ)/arteASCII.o

# ***************** LIBRERIAS ***************** #
$(LIB)/libimagen: $(OBJ)/imagen.o $(OBJ)/pgm.o
	ar rvs $(LIB)/libimagen.a $(OBJ)/imagen.o $(OBJ)/pgm.o

# ************ documentación *******
documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************
clean:
	rm $(BIN)/*
	rm $(OBJ)/*
