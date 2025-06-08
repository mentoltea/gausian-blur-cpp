CC=g++
FLAGS= #-ggdb -O0
BUILD_DIR=./build/
TARGET_NAME=main.exe
LIBS=-lm 

all: target

clean:
	rm -rf $(BUILD_DIR)

target: dir basic.o main.o alg.o conv.o
	$(CC) $(FLAGS) $(BUILD_DIR)basic.o $(BUILD_DIR)conv.o $(BUILD_DIR)alg.o $(BUILD_DIR)main.o -o $(BUILD_DIR)$(TARGET_NAME) $(LIBS)

basic.o: basic.cpp
	$(CC) $(FLAGS) -c basic.cpp -o $(BUILD_DIR)basic.o

conv.o: conv.cpp
	$(CC) $(FLAGS) -c conv.cpp -o $(BUILD_DIR)conv.o

alg.o: alg.cpp
	$(CC) $(FLAGS) -c alg.cpp -o $(BUILD_DIR)alg.o 

main.o: main.cpp
	$(CC) $(FLAGS) -c main.cpp -o $(BUILD_DIR)main.o

dir:
	mkdir -p $(BUILD_DIR)