EXEC=serveur
BIN_DIR=../../bin/serveur
LIB_DIR=../../lib/*.a

SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC)



$(EXEC): $(OBJ)
ifeq ($(LDFLAGS),)
	$(CC) -o $@ $^ $(LIB_DIR)
	@mv $(EXEC) $(BIN_DIR)/
else
	$(CC) -o $@ $^ $(LDFLAGS)
	@mv $(EXEC) $(BIN_DIR)/
endif	

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(EXEC)_clean:
	rm -rf *.o

mrproper: $(EXEC)_clean
	rm -rf $(BIN_DIR)/$(EXEC)

re: clean mrproper all

.PHONY: clean mrproper
