all:
	g++ -std=c++11 -g -o bin/debug src/*.cpp main.cpp -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

clean:
	rm -f ./bin/debug