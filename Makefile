SHELL = /bin/sh

# Where the files are
SRC_DIR = ./src
OBJ_DIR = ./objects

# Where to install
# For Windows/ReactOS:
#	Change INSTALL_DIR to C:\windows\system32\
#	Change INSTALL_COMMAND to move
#	Change EXECUTABLE_NAME to hdbf.exe
INSTALL_DIR = /usr/local/bin/
INSTALL_COMMAND = install
EXECUTABLE_NAME = hdbf

# Compiler flags
CFLAGS = -Wall -Wextra -pedantic -O2 -ansi
OBJECTS = $(addprefix $(OBJ_DIR)/,optimize.o binarytree.o hdbf.o main.o)

# Build recipe
$(EXECUTABLE_NAME): $(OBJ_DIR) $(OBJECTS)
	$(CC) -o $(EXECUTABLE_NAME) $(OBJECTS) $(CFLAGS)
$(OBJECTS): $(OBJ_DIR)%.o : $(SRC_DIR)%.c
	cc -c -o $@ $^ $(CFLAGS)
$(OBJ_DIR):
	mkdir $(OBJ_DIR)
install: hdbf
	$(INSTALL_COMMAND) $(EXECUTABLE_NAME) $(INSTALL_DIR)
uninstall:
	rm $(INSTALL_DIR)/$(EXECUTABLE_NAME)
clean: $(OBJ_DIR)
	rm -f $(EXECUTABLE_NAME) $(OBJECTS)
	rmdir $(OBJ_DIR)
