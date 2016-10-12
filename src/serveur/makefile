EXEC=serveur
BIN_DIR=../../bin/serveur


SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC)


$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)
	@mv $(EXEC) $(BIN_DIR)/
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC)_clean:
	rm -rf *.o

mrproper: $(EXEC)_clean
	rm -rf $(BIN_DIR)/$(EXEC)

re: clean mrproper all

.PHONY: clean mrproper
