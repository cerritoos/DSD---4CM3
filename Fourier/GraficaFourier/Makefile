
graf:  graficaFourier.o gfxModified.o
	g++ graficaFourier.o gfxModified.o -o graf -lX11 -lm
graficaFourier.o: graficaFourier.cpp gfxModified.o
	g++ graficaFourier.cpp -c
gfxModified.o: gfxModified.c gfxModified.h
	gcc gfxModified.c -c
