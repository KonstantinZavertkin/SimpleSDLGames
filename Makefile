GUI=./GUI/
GameRunner=./GameRunner/

CC=g++
CFLAGS=-Wall -Werror -g

INCUDE := include
SRC := src
OBJ := obj

GUI_SOURCES := $(wildcard $(GUI)$(SRC)/*.cpp)
GUI_OBJECTS := $(patsubst $(GUI)$(SRC)/%.cpp,$(GUI)$(OBJ)/%.o,$(GUI_SOURCES))

GameRunner_SOURCES := $(wildcard $(GameRunner)$(SRC)/*.cpp)
GameRunner_OBJECTS := $(patsubst $(GameRunner)$(SRC)/%.cpp,$(GameRunner)$(OBJ)/%.o,$(GameRunner_SOURCES))

$(info $(GUI_SOURCES))
$(info $(GUI_OBJECTS))

$(info $(GameRunner_SOURCES))
$(info $(GameRunner_OBJECTS))

# Create object files for GUI submodule
$(GUI)$(OBJ)/%.o: $(GUI)$(SRC)/%.cpp
	$(CC) $(CFLAGS) -I$(GUI)$(INCUDE)/ -c $< -o $@

# Create object files for GameRunner submodule
$(GameRunner)$(OBJ)/%.o: $(GameRunner)$(SRC)/%.cpp
	$(CC) $(CFLAGS) -I$(GUI)$(INCUDE)/ -c $< -o $@    # include GUI is not mistake

.PHONY: create_dirs

all: create_dirs run

create_dirs: $(GUI)$(OBJ) $(GameRunner)$(OBJ)

$(GUI)$(OBJ):
	mkdir -p $(GUI)$(OBJ)

$(GameRunner)$(OBJ):
	mkdir -p $(GameRunner)$(OBJ)

run: $(GUI_OBJECTS) $(GameRunner_OBJECTS)
	$(CC) $(CFLAGS) $^ -lSDL2 -o $@

clean:
	rm ./run
	rm -r $(GUI)$(OBJ)
	rm -r $(GameRunner)$(OBJ)
	mkdir -p $(GUI)$(OBJ)
	mkdir -p $(GameRunner)$(OBJ)
