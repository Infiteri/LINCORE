
BIN_DIR ?= Bin
UNAME_S := $(shell uname -s)

.PHONY: All

All:
ifeq ($(UNAME_S),Linux)
else
	@echo "Copying GLFW DLLs to $(BIN_DIR)..."
	cp -r Engine/Vendor/GLFW/lib $(BIN_DIR)/
endif

