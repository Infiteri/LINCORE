.PHONY: All

GP=Engine/Vendor/GLAD

.PHONY: Scaffold

All: Scaffold
	@gcc -fPIC -c -o $(OBJ_DIR)/glad.o $(GP)/src/glad.c -I$(GP)/include
	cp $(OBJ_DIR)/glad.o $(OBJ_DIR)/Engine/Source
	cp $(OBJ_DIR)/glad.o $(OBJ_DIR)/Editor/Source

Scaffold:
	mkdir -p $(OBJ_DIR)/Engine/Source
	mkdir -p $(OBJ_DIR)/Editor/Source
