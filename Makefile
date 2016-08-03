SHELL = /bin/sh

# Where the files are
SRC_DIR = ./src/

# Where to install
POSIX_DIR = /usr/local/bin/
WIN32_DIR = /windows/system32/

# Compiler flags
CC = cc # FreeBSD uses Clang, linked by 'cc'
CFLAGS = -Wall -Wextra -pedantic -O2 -ansi
FILES = optimize.c binarytree.c hdbf.c main.c
SOURCES = $(FILES:%.c=$(SRC_DIR)/%.c)

# Build recipe
hdbf:
	$(CC) -o hdbf $(SOURCES) $(CFLAGS)

# Clean nastiness
clean:
	rm -f hdbf hdbf.exe

# Install accroding to either POSIX or win32
install:
	install hdbf $(POSIX_DIR)

uninstall:
	rm  $(POSIX_DIR)hdbf
