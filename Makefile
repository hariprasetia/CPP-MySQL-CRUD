all: crud

crud: crud.o
		g++ -o crud crud.o -L/usr/lib -lmysqlcppconn

crud.o: crud.cpp
		g++ -c -I/usr/include/cppconn crud.cpp

clean:
		rm -f *.o crud
