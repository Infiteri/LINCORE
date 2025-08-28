ASSEMBLY=Editor
INCLUDE_FLAGS= -IEditor/Source -IEngine/Source
rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)) $(wildcard $1$2)

SRC_FILES := $(call rwildcard,$(ASSEMBLY)/Source/,*.cpp)
OBJ_FILES := $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

.PHONY: All Compile Link

All: Compile Link

Compile: $(OBJ_FILES)
	@echo Building $(ASSEMBLY)...

$(OBJ_DIR)/%.o: %.cpp
	@echo Compiling $<...
	@mkdir -p $(dir $@)
	@g++ -fPIC $< $(COMPILER_FLAGS) -c -o $@ $(DEFINES) $(INCLUDE_FLAGS) $(VENDOR_INCLUDES)

Link: $(OBJ_FILES)
	@echo Linking $(ASSEMBLY)...
	@g++ $(OBJ_FILES) $(OBJ_DIR)/Editor/Source/glad.o -fPIC -o $(BIN_DIR)/$(ASSEMBLY)$(EXE_EXT) $(LINKER_FLAGS) -lEngine -lImGui

