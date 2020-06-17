OBJ	= Main.o lib/sqlite3.o event/lisent.o event/requette.o package/bdd.o package/bukket.o package/connexion_reseau.o package/fichier.o package/find_node.o package/find_value.o package/node.o package/ping.o package/publish_key.o package/SendFileTCP.o package/send_udp.o package/store.o package/trouver_valeur.o utilitaires/console_color.o utilitaires/fileTabChar.o utilitaires/hashFile.o utilitaires/TCP.o utilitaires/UDP.o utilitaires/utilitaire.o
OUT	= kad
CC	 = gcc
CFLAGS	 = -W -Wall -pedantic
LDFLAGS	 = -lpthread -lcrypto -ldl
EXEC=kad
CMD = mpg123 .secret/assenceur.mp3 & make all

all: $(EXEC)

kad: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

Main.o: Main.c

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean mrproper

clean:
	rm -f $(OBJ)

music:
	${CMD}

