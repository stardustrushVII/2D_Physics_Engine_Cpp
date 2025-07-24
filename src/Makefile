CXX = clang++
CXXFLAGS = -std=c++20 -I/opt/homebrew/include -L/opt/homebrew/lib
SDLFLAGS = `sdl2-config --libs`

all: leveltest

leveltest:
	$(CXX) $(CXXFLAGS) src/leveltest.cpp -o build/leveltest $(SDLFLAGS)

clean:
	rm -f build/leveltest

