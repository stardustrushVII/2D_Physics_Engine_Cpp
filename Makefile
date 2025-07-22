# ---- CONFIG ----
CXX      = clang++
CXXFLAGS = -std=c++20 -Wall -Wextra -g \
           -Iinclude \
           -I/opt/homebrew/include \
           -I/opt/homebrew/opt/sdl2/include \
           -I/opt/homebrew/opt/sdl2_ttf/include

LDFLAGS  = -L/opt/homebrew/lib \
           -L/opt/homebrew/opt/sdl2/lib \
           -L/opt/homebrew/opt/sdl2_ttf/lib

LIBS     = -lSDL2 -lSDL2_ttf

SRC_DIR  = src
BUILD_DIR = build
BIN      = $(BUILD_DIR)/sonic

# ---- SOURCES ----
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# ---- RULES ----
all: $(BIN)

$(BIN): $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS) $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(BUILD_DIR)
