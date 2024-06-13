ROOT := ./cuba
ROOT_NAME := cuba

EXE := $(ROOT)/$(ROOT_NAME).exe
EXEJIT := $(ROOT)/$(ROOT_NAME)-jit.exe
EXETEST := $(ROOT)/test.exe

all: build build-jit

run-c: build
	./$(EXE)
	
run-j: build-jit
	./$(EXEJIT)

run-t: build-test
	./$(EXETEST)

build:
	gcc -o $(EXE) $(ROOT)/$(ROOT_NAME).c  

build-jit:
	gcc -o $(EXEJIT) $(ROOT)/$(ROOT_NAME)-jit.c

build-test:
	gcc -o $(EXETEST) $(ROOT)/test.c
	