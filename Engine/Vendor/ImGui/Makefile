
BIN_DIR ?= Bin
VP = Engine/Vendor

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)) $(wildcard $1$2)
SRC_FILES := $(call rwildcard,$(VP)/ImGui/,*.cpp)

GLFW_LINK = -L$(BIN_DIR) -lglfw3

LIB_EXT = .dll

.PHONY: All

All:
	g++ -g -fPIC -shared -I$(VP)/ImGui -I$(VP)/GLFW/include \
		$(SRC_FILES) $(GLFW_LINK) \
		-lopengl32 -lgdi32 -luser32 -lkernel32 -lshell32 -lcomdlg32 -lwinmm \
		-o $(VP)/ImGui/libImGui$(LIB_EXT)
	cp $(VP)/ImGui/libImGui$(LIB_EXT) $(BIN_DIR)/libImGui$(LIB_EXT)

