# Archivo makefile simple

PROYECTO=secuenciacion
DESTDIR=/usr/local/bin
CFLAGS=
LDFLAGS=-lm -lX11
CC=g++


all: $(PROYECTO)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

$(PROYECTO): $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	$(CC) $^ -o $@ $(LDFLAGS)


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
