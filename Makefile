CC=g++
CFLAGS=-Wall -Werror -g

INCUDE := include
SRC := src
OBJ := obj

SOURCES := $(wildcard $(SRC)/*.cpp)
OBJECTS := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SOURCES))

$(info $(SOURCES))
$(info $(OBJECTS))

$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) -I$(INCUDE)/ -c $< -o $@

all: $(OBJECTS)
	$(CC) $(CFLAGS) $^ -lSDL2 -o $@

clean:
	rm -r $(OBJ)
	rm ./all
	mkdir -p ./$(OBJ)
