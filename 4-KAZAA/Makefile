# Archivo makefile simple

PROYECTO=multicast
DESTDIR=/usr/local/bin
CFLAGS= 
LDFLAGS=-lm -pthread
CC=g++


all: $(PROYECTO)

%.o: %.cpp
	$(CC) -c $< $(CFLAGS) $(LDFLAGS) -std=c++11

$(PROYECTO): $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	$(CC) $^ -o $@ $(LDFLAGS) -std=c++11


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
