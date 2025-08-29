export BIN_DIR=Bin
export OBJ_DIR=Bin-Obj
export LINKER_FLAGS=-L$(BIN_DIR) 
export DEFINES = -D_DEBUG -DCE_WITH_EDITOR  
VP=-IEngine/Vendor
export VENDOR_INCLUDES=$(VP)/GLFW/include $(VP)/GLAD/include $(VP)/ImGui
export COMPILER_FLAGS = -g -std=c++2a -Wall 

ENGINE_ASSETS_PATH=EngineAssets

# Platform dependence
export UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
export LIB_EXT=.so
export EXE_EXT=
export GLFW_LIB=glfw
else
export LIB_EXT=.dll
export EXE_EXT=.exe
export GLFW_LIB=glfw3
endif

.PHONY: All Scaffold Engine Editor Clean Vendor Tests Assets Full

All: Scaffold Engine Editor Assets

Full: Scaffold Vendor Assets Engine Editor

Assets:
	@cp Shader.glsl $(BIN_DIR)/Shader.glsl
	@cp -r Engine/Assets $(BIN_DIR)/$(ENGINE_ASSETS_PATH)

Engine: Scaffold
	@$(MAKE) -f Engine/Makefile All -j8

Editor: Scaffold
	@$(MAKE) -f Editor/Makefile All -j8

Vendor: Scaffold
	@$(MAKE) -f Engine/Vendor/GLFW/Makefile -j12 All
	@$(MAKE) -f Engine/Vendor/GLAD/Makefile -j12
	@$(MAKE) -f Engine/Vendor/ImGui/Makefile -j12

Scaffold:
	@echo "Scaffolding ..."
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

Tests:
	@$(MAKE) -f Tests/Makefile -j8

Clean:
	@echo "Cleaning ..."
	rm -r $(BIN_DIR)
	rm -r $(OBJ_DIR)

