# define which compiler to use
CXX    := g++
OUTPUT := sfmlgame

# if you need to manually specify your SFML install dir, do so here
SFML_DIR := .

# compiler and linking flags
OPT 	  := -O3
CXX_FLAGS := $(OPT) -std=c++17
INCLUDES  := -I./src -I$(SFML_DIR)/include
LDFLAGS   := $(OPT) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -L$(SFMLDIR)/lib

# stackoverflow.com/questions/11184389/what-does-wildcard-mean-in-makefile
# the source files for the ECS game engine
SRC_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(SRC_FILES:.cpp=.o)

# all of these targets will be made if you just type make
all:$(OUTPUT)

# stackoverflow.com/questions/3220277/what-do-the-makefile-symbols-and-mean
# define main executable requirements/commands
$(OUTPUT):$(OBJ_FILES) Makefile
	$(CXX) $(OBJ_FILES) $(LDFLAGS) -o ./bin/$@

# specifies how the objects are compiled from cpp files
.cpp.o:
	$(CXX) -c $(CXX_FLAGS) $(INCLUDES) $< -o $@

# typing 'make clean' will remove all intermediate build files
clean:
	rm -f $(OBJ_SFMLGAME) ./bin/sfmlgame

# typing 'make run' will compile and run the program
run: $(OUTPUT)
	cd bin && ./sfmlgame && cd ..
