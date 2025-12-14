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
SOURCES = main.cpp ULveWindow.cpp Ulve_pipeline.cpp ULve_device.cpp ../../Vulkan/VulkanCore.cpp

# Output executable
TARGET = TutorialApp

# Compiler
CXX = clang++

# Shader compiler
GLSLC = glslc

# Shader sources and targets
SHADER_DIR = ../shaders
VERT_SOURCES = $(wildcard $(SHADER_DIR)/*.vert)
FRAG_SOURCES = $(wildcard $(SHADER_DIR)/*.frag)
VERT_SPV = $(VERT_SOURCES:.vert=.vert.spv)
FRAG_SPV = $(FRAG_SOURCES:.frag=.frag.spv)

all: shaders $(TARGET)

shaders: $(VERT_SPV) $(FRAG_SPV)

%.vert.spv: %.vert
	$(GLSLC) $< -o $@

%.frag.spv: %.frag
	$(GLSLC) $< -o $@

$(TARGET): $(SOURCES)
	$(CXX) $(CFLAGS) $(INCLUDE_DIRS) $(LIB_DIRS) $(SOURCES) $(LDFLAGS) -o $(TARGET)

.PHONY: test clean

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
