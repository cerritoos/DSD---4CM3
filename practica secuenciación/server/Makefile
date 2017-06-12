servidor: Servidor.cpp PaqueteDatagrama.o
	g++ Servidor.cpp PaqueteDatagrama.o SocketDatagrama.o -o servidor
PaqueteDatagrama.o: PaqueteDatagrama.cpp SocketDatagrama.o PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h
	g++ SocketDatagrama.cpp -c
