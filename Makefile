# Makefile for SFML project

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -I/opt/homebrew/include/ -Iinclude/

# Linker flags
LDFLAGS = -L/opt/homebrew/lib -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRCS = \
src/main.cpp src/entities/entity.cpp src/manager/manager.cpp src/entities/spaceship.cpp src/entities/projectile.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = game

# Default target
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

# Compile the source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the project
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
