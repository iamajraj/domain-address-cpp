CPP=g++
CFLAGS=-L./lib -lwsock32

all: main.cpp
	$(CPP) $(CFLAGS) main.cpp -o main.exe
