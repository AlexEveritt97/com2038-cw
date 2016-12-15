TARGET = main
INCDIR = include
SRCDIR = src
OBJDIR = obj
BINDIR = bin

CC = g++

FLAGS = -Wall -I$(INCDIR)
CFLAGS = -g $(FLAGS)
LFLAGS = $(FLAGS) -lm
LINKER = g++ -o

SOURCES 	:= $(wildcard $(SRCDIR)/*.cpp)
INCLUDES 	:= $(wildcard $(INCDIR)/*.h)
OBJECTS 	:= $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)

$(BINDIR)/$(TARGET): $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJECTS)

$(OBJECTS): $(OBJDIR)%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@