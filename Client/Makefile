#Compiler is G++ from MinGW
CC = g++

#Library directory
LDIR = ./lib

#Include directory
IDIR = ./include

#Source directory
SDIR = ./src

#.o Directory
ODIR = ./obj

#Arguments to pass to the compiler
CFLAGS = -std=c++11 -Wall -I$(IDIR) -DSFML_STATIC

#Libraries that will be used
LIBS = -L$(LDIR) -lsfml-graphics-s -lsfml-network-s -lsfml-window-s -lsfml-system-s -lsfml-main

#Removes the console window on release
RELEASE = -Wl,-subsystem,windows

#Dependancies
_DEPS = $(wildcard *.h)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#Source Files
_SRC = Main.cc Application.cc Network.cc \
LoginState.cc MainState.cc GameState.cc \
Entity.cc ObjectManager.cc Player.cc Sprite.cc Animation.cc \
View.cc MainView.cc Map.cc Tile.cc \
Controller.cc PlayerController.cc

#Objects
_OBJ = $(_SRC:.cc=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#Executable name
EXECUTABLE = Client


all: $(EXECUTABLE)

$(ODIR)/%.o: $(SDIR)/%.cc $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $<

$(EXECUTABLE): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

run:
	./$(EXECUTABLE)

.PHONY: clean cleanest

clean:
	del obj\*.o

cleanest: clean
	del $(EXECUTABLE).exe