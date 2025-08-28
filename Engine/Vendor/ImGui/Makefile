VP=Engine/Vendor
BUILD_DIR?=Bin

rwildcard=$(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2)) $(wildcard $1$2)

SRC_FILES := $(call rwildcard,$(VP)/ImGui/,*.cpp)

.PHONY: All

All:
	g++ -g -fPIC -shared -I$(VP)/ImGui -I$(VP)/GLFW/include -L$(BUILD_DIR) -lglfw $(SRC_FILES) -o $(VP)/ImGui/libImGui$(LIB_EXT)
	cp $(VP)/ImGui/libImGui$(LIB_EXT) $(BUILD_DIR)/libImGui$(LIB_EXT)
