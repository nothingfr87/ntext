LIBS = $(shell pkg-config --libs --cflags ncursesw)
CFLAGS = $(LIBS) -O3
CC = gcc
BIN = ntext
INSTALL_DIR = /usr/local/bin/

all: clean build

install: clean build
	sudo chmod 777 $(BIN)
	sudo mv $(BIN) $(INSTALL_DIR)

build:
	$(CC) src/*.c -o $(BIN) $(CFLAGS)

clean:
	rm -f $(BIN) 2>/dev/null
