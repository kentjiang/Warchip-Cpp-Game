CC = g++
FLAG = -I/usr/include/SDL -std=c++11 -ggdb3 
SDL = -lSDL -lSDL_image -lSDL_mixer -lSDL_ttf
EXECUTABLE = warchip

warchip : main.cpp
	$(CC) $(FLAG) main.cpp -o $(EXECUTABLE) $(SDL)

clean:
	rm -f *.o $(EXECUTABLE)
