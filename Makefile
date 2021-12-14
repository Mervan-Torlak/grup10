VPATH   =   ./src
CXXFLAGS=   gcc -I  "./include/" -o

all: Dosyalar Olustur Calistir

Dosyalar:
	$(CXXFLAGS)  ./lib/shell.o  -c ./src/shell.c

Olustur:
	$(CXXFLAGS)  ./bin/Derle  ./lib/shell.o  ./src/main.c

Calistir:
	./bin/Derle
