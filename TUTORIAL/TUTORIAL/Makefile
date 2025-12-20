CFLAGS = -std=c++20 -O2

# Detect OS
UNAME_S := $(shell uname -s)

# Base target name
TARGET_NAME = TutorialApp

ifeq ($(UNAME_S), Darwin)
	# macOS specific settings
	# Assuming Homebrew installation
	VULKAN_SDK_PATH = $(shell brew --prefix vulkan-headers)
	GLFW_PATH = $(shell brew --prefix glfw)
	
	INCLUDE_DIRS = -I. -I../../Vulkan -I$(GLFW_PATH)/include -I$(VULKAN_SDK_PATH)/include
	LDFLAGS = -L$(GLFW_PATH)/lib -L$(shell brew --prefix vulkan-loader)/lib -lglfw -lvulkan -framework Cocoa -framework IOKit -framework CoreVideo
	
	GLSLC = glslc
	CLEAN_CMD = rm -f
	TARGET = $(TARGET_NAME)
else
	# Windows specific settings (original)
	LDFLAGS = -L./glfw/lib-mingw-w64 -L./VulkanSDK/1.4.309.0/Lib -lglfw3 -lvulkan-1 -lgdi32 -luser32 -lkernel32
	INCLUDE_DIRS = -I. -I../../Vulkan -I./glfw/include -I./VulkanSDK/1.4.309.0/Include
	GLSLC = ./VulkanSDK/1.4.309.0/Bin/glslc.exe
	CLEAN_CMD = del
	TARGET = $(TARGET_NAME).exe
endif

# Source files
SOURCES = main.cpp ULveWindow.cpp Ulve_pipeline.cpp ULve_device.cpp ULve_swap_chain.cpp ULve_model.cpp ULve_renderer.cpp simple_render_system.cpp first_app.cpp ../../Vulkan/VulkanCore.cpp


# Compiler
CXX = g++

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
	$(CLEAN_CMD) $(TARGET)
	$(CLEAN_CMD) $(VERT_SPV)
	$(CLEAN_CMD) $(FRAG_SPV)
