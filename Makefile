TARGET = svggen
SRC = main.cpp
CC = g++
CXXFLAGS = -std=c++11

all: $(SRC)
	$(CC) $(CXXFLAGS) $(SRC) -o $(TARGET)


genall: all
	@for i in `seq 1 3`; do ./$(TARGET) $$i > test-$$i.svg; done
