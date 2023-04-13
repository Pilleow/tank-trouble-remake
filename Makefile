MAIN = main

SRC_FLAGS = -std=c++14 -m64 -g -Wall -I include
MAIN_FLAGS = -lSDL2main -lSDL2 -lSDL2_image

P_OUT = bin/debug
P_SRC = src

GXX = g++

bin/debug/main: $(MAIN)
	./$(P_OUT)/$(MAIN)
	$(RM) -r *.o

main: 
	$(GXX) -c $(P_SRC)/*.cpp $(SRC_FLAGS)
	$(GXX) *.o -o $(P_OUT)/$(MAIN) $(MAIN_FLAGS)

.PHONY: clean
clean: 
	$(RM) -r *.o