# Archivo makefile simple

PROYECTO=hilos
DESTDIR=/usr/local/bin
LDFLAGS=-pthread


all: $(PROYECTO)

%.o: %.cpp
	g++ -c -std=c++11 -pthread $<

$(PROYECTO): $(patsubst %.cpp,%.o,$(wildcard *.cpp))
	g++ $^ -std=c++11 -o $@ -pthread


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
