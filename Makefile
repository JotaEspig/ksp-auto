CC=g++
CC_FLAGS=-std=c++11 \
		 -lkrpc 	\
		 -lprotobuf

SRC=$(wildcard src/*.cpp)
TARGET_NAME=ksp-auto

IP=127.0.0.1

all:
	$(CC) main.cpp $(SRC) $(CC_FLAGS) -o $(TARGET_NAME) 

run: all
	@ ./$(TARGET_NAME) $(IP)
