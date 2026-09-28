CC=gcc
CFLAGS=-Wall -Wextra

all: producer_primes producer_evens producer_chars consumer

producer_primes: producer_primes.c common.h
	$(CC) $(CFLAGS) -o producer_primes producer_primes.c

producer_evens: producer_evens.c common.h
	$(CC) $(CFLAGS) -o producer_evens producer_evens.c

producer_chars: producer_chars.c common.h
	$(CC) $(CFLAGS) -o producer_chars producer_chars.c

consumer: consumer.c common.h
	$(CC) $(CFLAGS) -o consumer consumer.c

clean:
	rm -f producer_primes producer_evens producer_chars consumer
