SHELL = /bin/sh

# Where the files are
SRC_DIR = ./src/

# Where to install
# If running on Windows/ReactOS, change INSTALL_DIR
# to some folder in %PATH%, and EXECUTABLE_NAME to
# hdbf.exe
INSTALL_DIR = /usr/local/bin/
EXECUTABLE_NAME = hdbf

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
