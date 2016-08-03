SHELL = /bin/sh

# Where the files are
SRC_DIR = ./src/

# Where to install
ifeq ($(OS),Windows_NT)
	EXECUTABLE_NAME  = hdbf.exe
	INSTALL_DIR = /windows/system32/
else
	EXECUTABLE_NAME = hdbf
	INSTALL_DIR = /usr/local/bin/
endif

# Compiler flags
CC = cc # FreeBSD uses Clang, linked by 'cc'
CFLAGS = -Wall -Wextra -pedantic -O2 -ansi
FILES = optimize.c binarytree.c hdbf.c main.c
SOURCES = $(FILES:%.c=$(SRC_DIR)/%.c)

# Build recipe
hdbf:
	$(CC) -o $(EXECUTABLE_NAME) $(SOURCES) $(CFLAGS)

# Clean nastiness
clean:
	rm -f $(EXECUTABLE_NAME)

# Install according to either POSIX or win32
install:
	install $(EXECUTABLE_NAME) $(INSTALL_DIR)
uninstall:
	rm  $(INSTALL_DIR)hdbf
