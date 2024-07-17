# Compiler
CXX = g++

SFML_INCLUDE_DIR = /opt/homebrew/include/
SFML_LIB_DIR = /opt/homebrew/lib/

CXXFLAGS = -std=c++14 -Wall -I$(SFML_INCLUDE_DIR) -Iinclude/
LDFLAGS = -L$(SFML_LIB_DIR) -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Source files
SRCS = \
src/main.cpp src/entities/entity.cpp src/manager/manager.cpp \
src/entities/spaceship.cpp src/entities/projectile.cpp src/sprites/animated.cpp \
src/manager/spawner.cpp src/entities/enemy.cpp src/ui/button.cpp

OBJS = $(SRCS:.cpp=.o)

# Executable name
TARGET = game

# Default target
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean the project
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
