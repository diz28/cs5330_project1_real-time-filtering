

CC = g++
PROJECT = vidDisplay
SRC = vidDisplay.cpp filter.cpp
LIBS = `pkg-config --cflags --libs opencv4`
$(PROJECT) : $(SRC)
	$(CC) $(SRC) -o $(PROJECT) $(LIBS)
