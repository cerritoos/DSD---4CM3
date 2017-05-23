servidor: Cliente.cpp PaqueteDatagrama.o
	g++ Cliente.cpp PaqueteDatagrama.o SocketDatagrama.o -o Cliente
PaqueteDatagrama.o: PaqueteDatagrama.cpp SocketDatagrama.o PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h
	g++ SocketDatagrama.cpp -c
