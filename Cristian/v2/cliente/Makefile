# Archivo makefile simple

PROYECTO=cristian
DESTDIR=/usr/local/bin
CFLAGS=
LDFLAGS=-lm -lX11
CC=g++


all: $(PROYECTO)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO): gfxModified.o $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	$(CC) $^ -o $@ $(LDFLAGS)

gfxModified.o: gfxModified.c
	gcc -c gfxModified.c


.PHONY: clean

install: all
	if [ ! -d $(DESTDIR) ]; then \
		sudo $(DESTDIR); \
	fi; \
	sudo cp $(PROYECTO) $(DESTDIR)

uninstall:
	rm $(DESTDIR)/$(PROYECTO)

clean:
	 -rm -f *.o $(PROYECTO)
