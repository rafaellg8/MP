SRC = src
INC = include
OBJ = obj
BIN = bin
LIB = lib

CXX = g++
CPPFLAGS = -Wall -g -ansi -std=c++11 -I$(INC)


all: $(BIN)/arteASCII $(BIN)/testarteASCII $(BIN)/testplano $(BIN)/testimagen $(BIN)/arteASCII2 $(BIN)/suma $(BIN)/testListas

$(BIN)/testplano: $(SRC)/testplano.cpp $(LIB)/libimagen.a
	$(CXX) $(CPPFLAGS) $(SRC)/testplano.cpp $(LIB)/libimagen.a $(OBJ)/byte.o -o $(BIN)/testplano

$(BIN)/testarteASCII: $(SRC)/testarteASCII.cpp $(LIB)/libimagen.a
	$(CXX) $(CPPFLAGS) $(SRC)/testarteASCII.cpp $(LIB)/libimagen.a $(OBJ)/byte.o -o $(BIN)/testarteASCII

$(BIN)/arteASCII: $(SRC)/arteASCII.cpp $(LIB)/libimagen.a
	$(CXX) $(CPPFLAGS) $(SRC)/arteASCII.cpp $(LIB)/libimagen.a $(OBJ)/byte.o -o $(BIN)/arteASCII

$(BIN)/arteASCII2: $(SRC)/arteASCII2.cpp $(LIB)/libimagen.a $(OBJ)/lista.o
	$(CXX) $(CPPFLAGS) $(SRC)/arteASCII2.cpp $(LIB)/libimagen.a $(OBJ)/byte.o -o $(BIN)/arteASCII2

$(BIN)/testimagen: $(SRC)/testimagen.cpp $(LIB)/libimagen.a
	$(CXX) $(CPPFLAGS) $(SRC)/testimagen.cpp $(LIB)/libimagen.a $(OBJ)/byte.o -o $(BIN)/testimagen

$(BIN)/suma: $(SRC)/suma.cpp $(LIB)/libimagen.a
		$(CXX) $(CPPFLAGS) $(SRC)/suma.cpp $(LIB)/libimagen.a $(OBJ)/byte.o -o $(BIN)/suma

$(BIN)/testListas: $(SRC)/testListas.cpp $(LIB)/libimagen.a
	$(CXX) $(CPPFLAGS) $(SRC)/testListas.cpp $(LIB)/libimagen.a $(OBJ)/byte.o -o $(BIN)/testListas

$(LIB)/libimagen.a : $(OBJ)/pgm.o $(OBJ)/imagen.o $(SRC)/imagen.cpp $(OBJ)/lista.o
	ar rvs $(LIB)/libimagen.a $(OBJ)/pgm.o $(OBJ)/imagen.o $(OBJ)/lista.o

$(OBJ)/imagen.o : $(INC)/imagen.h $(SRC)/imagen.cpp $(OBJ)/byte.o $(OBJ)/pgm.o $(OBJ)/lista.o
	$(CXX) -c $(CPPFLAGS) $(SRC)/imagen.cpp -o $(OBJ)/imagen.o

$(OBJ)/pgm.o : $(INC)/pgm.h $(SRC)/pgm.cpp
	$(CXX) -c $(CPPFLAGS) $(SRC)/pgm.cpp -o $(OBJ)/pgm.o

$(OBJ)/byte.o : $(INC)/byte.h $(SRC)/byte.cpp
	$(CXX) -c $(CPPFLAGS) $(SRC)/byte.cpp -o $(OBJ)/byte.o

$(OBJ)/lista.o : $(SRC)/lista.cpp
	$(CXX) -c $(CPPFLAGS) $(SRC)/lista.cpp -o $(OBJ)/lista.o

# ************ documentación *******

documentacion:
	doxygen doc/doxys/Doxyfile

# ************ Limpieza ************

clean:
	rm $(OBJ)/* $(BIN)/* $(LIB)/*

mr_proper: clean
	rm *.pgm
	rm ascii*
