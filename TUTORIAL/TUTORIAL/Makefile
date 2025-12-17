CFLAGS = -std=c++20 -O2
LDFLAGS = -L./glfw/lib-mingw-w64 -L./VulkanSDK/1.4.309.0/Lib -lglfw3 -lvulkan-1 -lgdi32 -luser32 -lkernel32

# Include paths
INCLUDE_DIRS = -I. -I../../Vulkan -I./glfw/include -I./VulkanSDK/1.4.309.0/Include

# Source files
SOURCES = main.cpp ULveWindow.cpp Ulve_pipeline.cpp ULve_device.cpp ULve_swap_chain.cpp ULve_model.cpp ULve_gameobject.cpp first_app.cpp ../../Vulkan/VulkanCore.cpp

# Output executable
TARGET = TutorialApp.exe

# Compiler
CXX = g++

# Shader compiler
GLSLC = ./VulkanSDK/1.4.309.0/Bin/glslc.exe

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
	$(CXX) $(CFLAGS) $(INCLUDE_DIRS) $(SOURCES) $(LDFLAGS) -o $(TARGET)

.PHONY: test clean

test: $(TARGET)
	./$(TARGET)

clean:
	del $(TARGET)
	del $(subst /,\,$(VERT_SPV))
	del $(subst /,\,$(FRAG_SPV))
