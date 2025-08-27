SRC_DIR = Tests
OBJ_DIR ?= Bin-Obj
BIN_DIR ?= Bin
TARGET  = $(BIN_DIR)/TestApp

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/$(SRC_DIR)/%.o, $(SRC_FILES))

CXX = g++
CXXFLAGS = -std=c++20 -O2 -Wall -IEngine/Source -ITests $(VENDOR_INCLUDES) -g 
LDFLAGS = -L$(BIN_DIR) -lEngine $(OBJ_DIR)/glad.o -lglfw

All: $(TARGET)

$(TARGET): $(OBJ_FILES) | $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)/$(SRC_DIR)
	@echo Compiling $^...
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/$(SRC_DIR):
	mkdir -p $@

$(BIN_DIR):
	mkdir -p $@

Clean:
	rm -rf $(OBJ_DIR)/$(SRC_DIR)/*.o $(TARGET)

