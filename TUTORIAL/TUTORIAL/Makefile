CFLAGS = -std=c++20 -O2
LDFLAGS = -lglfw -lvulkan -ldl -lpthread -framework Cocoa -framework IOKit -framework CoreVideo

# Detect OS and adjust paths/flags if necessary (optional, but good for portability)
# For now, focusing on macOS as requested.

# Include paths
# Assuming Vulkan SDK and GLFW are installed via Homebrew or in standard locations
INCLUDE_DIRS = -I. -I../../Vulkan -I/opt/homebrew/include -I/usr/local/include

# Library paths
LIB_DIRS = -L/opt/homebrew/lib -L/usr/local/lib

# Source files
SOURCES = main.cpp ULveWindow.cpp ../../Vulkan/VulkanCore.cpp

# Output executable
TARGET = TutorialApp

# Compiler
CXX = clang++

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CFLAGS) $(INCLUDE_DIRS) $(LIB_DIRS) $(SOURCES) $(LDFLAGS) -o $(TARGET)

.PHONY: test clean

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
