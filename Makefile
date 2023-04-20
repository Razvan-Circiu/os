CC = gcc
CFLAGS = -O3 -Wall
TARGET = os-project

all: $(TARGET)

$(TARGET): fisiere.o main.o
	$(CC) $(CFLAGS) -o $(TARGET).x *.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

fisiere.o: fisiere.c fisiere.h
	$(CC) $(CFLAGS) -c fisiere.c

clean:
	rm *.x *.o

run: ./$(TARGET).x
	./$(TARGET).x $(ARGS)
