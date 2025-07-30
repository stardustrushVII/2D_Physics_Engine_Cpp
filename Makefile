CXX = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -I/opt/homebrew/include -Iinclude
LDFLAGS = -L/opt/homebrew/lib `sdl2-config --libs` -lSDL2_ttf
BUILD_DIR = build

SRC_DIR = src

all: build/Stardust_Engine build/leveltest

build/Stardust_Engine: \
    $(SRC_DIR)/main.cpp \
	$(SRC_DIR)/resolution_selector.cpp \
	$(SRC_DIR)/input.cpp \
    $(SRC_DIR)/player.cpp \
    $(SRC_DIR)/tilemap.cpp \
    $(SRC_DIR)/physics.cpp	\
	$(SRC_DIR)/pause.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

build/leveltest: src/leveltest.cpp src/player.cpp src/tilemap.cpp src/physics.cpp src/input.cpp	src/resolution_selector.cpp	src/pause.cpp
	$(CXX) $(CXXFLAGS) -I/opt/homebrew/include -Iinclude \
	$^ -o $@ -L/opt/homebrew/lib `sdl2-config --libs` -lSDL2_ttf

clean:
	rm -rf build/*.o build/stardust_engine build/leveltest
