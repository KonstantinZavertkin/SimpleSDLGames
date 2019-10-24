GUI=./GUI/
GameBackend=./GameBackend/
GameRunner=./GameRunner/

CC=g++
CFLAGS=-std=c++17 -Wall -Werror -g

INCUDE := include
SRC := src
OBJ := obj

GUI_SOURCES := $(wildcard $(GUI)$(SRC)/*.cpp)
GUI_OBJECTS := $(patsubst $(GUI)$(SRC)/%.cpp,$(GUI)$(OBJ)/%.o,$(GUI_SOURCES))

GameBackend_SOURCES := $(wildcard $(GameBackend)$(SRC)/*.cpp)
GameBackend_OBJECTS := $(patsubst $(GameBackend)$(SRC)/%.cpp,$(GameBackend)$(OBJ)/%.o,$(GameBackend_SOURCES))

GameRunner_SOURCES := $(wildcard $(GameRunner)$(SRC)/*.cpp)
GameRunner_OBJECTS := $(patsubst $(GameRunner)$(SRC)/%.cpp,$(GameRunner)$(OBJ)/%.o,$(GameRunner_SOURCES))

$(info $(GUI_SOURCES))
$(info $(GUI_OBJECTS))

$(info $(GameBackend_SOURCES))
$(info $(GameBackend_OBJECTS))

$(info $(GameRunner_SOURCES))
$(info $(GameRunner_OBJECTS))

# Create object files for GUI submodule
$(GUI)$(OBJ)/%.o: $(GUI)$(SRC)/%.cpp
	$(CC) $(CFLAGS) -I$(GUI)$(INCUDE)/ -c $< -o $@

# Create object files for GUI submodule
$(GameBackend)$(OBJ)/%.o: $(GameBackend)$(SRC)/%.cpp
	$(CC) $(CFLAGS) -I$(GameBackend)$(INCUDE)/ -c $< -o $@

# Create object files for GameRunner submodule
$(GameRunner)$(OBJ)/%.o: $(GameRunner)$(SRC)/%.cpp
	$(CC) $(CFLAGS) -I$(GUI)$(INCUDE)/ -I$(GameBackend)$(INCUDE)/ -I$(GameRunner)$(INCUDE) -c $< -o $@

.PHONY: create_dirs

all: create_dirs run

create_dirs: $(GUI)$(OBJ) $(GameRunner)$(OBJ) $(GameBackend)$(OBJ)

$(GUI)$(OBJ):
	mkdir -p $(GUI)$(OBJ)

$(GameBackend)$(OBJ):
	mkdir -p $(GameBackend)$(OBJ)

$(GameRunner)$(OBJ):
	mkdir -p $(GameRunner)$(OBJ)

run: $(GUI_OBJECTS) $(GameBackend_OBJECTS) $(GameRunner_OBJECTS)
	$(CC) $(CFLAGS) $^ -lSDL2 -o $@

clean:
	rm ./run
	rm -r $(GUI)$(OBJ)
	rm -r $(GameBackend)$(OBJ)
	rm -r $(GameRunner)$(OBJ)
	mkdir -p $(GUI)$(OBJ)
	mkdir -p $(GameBackend)$(OBJ)
	mkdir -p $(GameRunner)$(OBJ)
