export BIN_DIR=Bin
export OBJ_DIR=Bin-Obj
export LINKER_FLAGS=-L$(BIN_DIR) 
export DEFINES = -D_DEBUG -DCE_WITH_EDITOR  
VP=-IEngine/Vendor
export VENDOR_INCLUDES=$(VP)/GLFW/include $(VP)/GLAD/include $(VP)/ImGui
export COMPILER_FLAGS = -g -std=c++2a -Wall 

# Platform dependence
export UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
export LIB_EXT=.so
export EXE_EXT=
else
export LIB_EXT=.dll
export EXE_EXT=.exe
endif

.PHONY: All Scaffold Engine Editor Clean Run Vendor Tests Assets

All: Scaffold Engine Editor Assets

Assets:
	@cp Shader.glsl $(BIN_DIR)/Shader.glsl
	@cp Screen.glsl $(BIN_DIR)/Screen.glsl

Engine: Scaffold
	@$(MAKE) -f Engine/Makefile All -j8

Editor: Scaffold
	@$(MAKE) -f Editor/Makefile All -j8

Vendor:
	@$(MAKE) -f Engine/Vendor/GLFW/Makefile -j8
	@$(MAKE) -f Engine/Vendor/GLAD/Makefile -j8
	@$(MAKE) -f Engine/Vendor/ImGui/Makefile -j8

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

