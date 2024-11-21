CC=gcc
CFLAGS=-O

all: test_open test_copy test_cat test_dup test_hotel

test_open: test_open.o
	$(CC) -o $@ $<
test_copy: test_copy.o
	$(CC) -o $@ $<
test_cat: test_cat.o
	$(CC) -o $@ $<
test_dup: test_dup.o
	$(CC) -o $@ $<
test_hotel: test_hotel.o
	$(CC) -o $@ $<
%.o: %.c
	$(CC) -c -o $@ $<
clean:
	rm *.o test_open test_copy test_cat test_dup test_hotel
