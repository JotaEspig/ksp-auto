CC=g++
CC_FLAGS=-std=c++11 \
		 -lkrpc 	\
		 -lprotobuf

SRC=$(wildcard src/*.cpp)
TARGET_NAME=ksp-auto

IP=127.0.0.1

all: dir
	$(CC) main.cpp $(SRC) $(CC_FLAGS) -o ./bin/$(TARGET_NAME)

dir:
	if [ ! -d "./bin" ]; then mkdir bin; fi

run: all
	@ ./bin/$(TARGET_NAME) $(IP)
