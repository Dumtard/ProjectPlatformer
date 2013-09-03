#Compiler is G++ from MinGW
CC = g++

#Library directory
LDIR = -L./lib -LC:/"Program Files (x86)"/MySQL/"MySQL Server 5.6"/lib -LC:/MySQL++/3.2.0/lib

#Include directory
IDIR = -I./include -IC:/"Program Files (x86)"/MySQL/"MySQL Server 5.6"/include -IC:/MySQL++/3.2.0/include

#Source directory
SDIR = ./src

#.o Directory
ODIR = ./obj

#Arguments to pass to the compiler
CFLAGS = -std=c++11 $(IDIR) -DSFML_STATIC

#Libraries that will be used
LIBS = $(LDIR) -lsfml-network-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lmysqlpp -lmysqlclient

#Dependancies
_DEPS = $(wildcard *.h)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

#Source Files
_SRC = Server.cc Main.cc Player.cc Map.cc

#Objects
_OBJ = $(_SRC:.cc=.o)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

#Executable name
SERVER = Server


all: $(SERVER)

$(ODIR)/%.o: $(SDIR)/%.cc $(DEPS)
	$(CC) -c $(CFLAGS) -o $@ $<

$(SERVER): $(OBJ)
	$(CC) -o $@ $^ $(LIBS)

.PHONY: clean cleanest

clean:
	del obj\*.o

cleanest: clean
	del $(SERVER).exe