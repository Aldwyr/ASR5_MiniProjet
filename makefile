export CC=gcc
export CFLAGS=-W -Wall -ansi -pedantic -std=c11
export LDFLAGS=


CLIENT_DIR=src/client
SERVEUR_DIR=src/serveur

CLIENT_BIN=bin/client
SERVEUR_BIN=bin/serveur

EXEC_CLIENT=client
EXEC_SERVEUR=serveur



all: $(EXEC_CLIENT) $(EXEC_SERVEUR)


$(EXEC_CLIENT):
	@(cd $(CLIENT_DIR) && $(MAKE))

$(EXEC_SERVEUR):
	@(cd $(SERVEUR_DIR) && $(MAKE))

clean: client_clean serveur_clean


client_clean:
	@(cd $(CLIENT_DIR) && $(MAKE) $@)

serveur_clean:
	@(cd $(SERVEUR_DIR) && $(MAKE) $@)

mrproper: clean
	rm -rf $(CLIENT_BIN)/$(EXEC_CLIENT)
	rm -rf $(SERVEUR_BIN)/$(EXEC_SERVEUR)

re: clean mrproper all

.PHONY: clean mrproper
