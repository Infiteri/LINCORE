ASSEMBLY=Engine
INCLUDE_FLAGS=-IEngine/Source $(VENDOR_INCLUDES)
LNK = $(LINKER_FLAGS) -L$(BIN_DIR) -Wl,-rpath=$(BIN_DIR) -lglfw -lImGui

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
	@g++ -fPIC $< $(COMPILER_FLAGS) -c -o $@ $(DEFINES) $(INCLUDE_FLAGS)

Link: $(OBJ_FILES)
	@echo Linking $(ASSEMBLY)...
	@g++ -shared -fPIC $(OBJ_FILES) -o $(BIN_DIR)/libEngine$(LIB_EXT) $(LNK)
