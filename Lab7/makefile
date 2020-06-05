CC = gcc
TARGET = laba7.exe


.PHONY: all run clean build

all: $(TARGET)

clean:
	@rm -rf $(TARGET) *.o *.i *.s *.gch *.out *.exe

build: $(TARGET)

Lab7var15.o: Lab7.c
			$(CC) -c Lab7.c


$(TARGET): Lab7.o
			$(CC) -o $(TARGET) Lab7.o


run:
	$(TARGET)
