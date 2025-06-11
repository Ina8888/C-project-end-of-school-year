
all: shuffle encrypt deck_game

shuffle: shuffle.c
	gcc -o shuffle shuffle.c

encrypt: encryption.c
	gcc -c -DENCRYPT_MAIN -o encrypt encryption.c

deck_game: karti.c encryption.c
	gcc -o deck_game karti.c encryption.c

clean:
	rm -f shuffle encrypt deck_game 