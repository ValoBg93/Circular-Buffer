main.exe: main.o
	g++ -static-libgcc -static-libstdc++ main.o -o main.exe

main.o: ./src/main.cpp
	g++ -c -I./headers ./src/main.cpp -o main.o

.PHONY: clean
clean:
	-rm -f *.o main.exe
