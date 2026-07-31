CC := clang

BUILD_PATH := build
BIN_PATH   := bin
SRC_PATH 	 := src

COMPILATION_FLAGS := -Wall -Wextra -g -O3 -I$(SRC_PATH) -c -std=c23
LINKER_FLAGS 			:=

CORE_SRC := $(shell find $(SRC_PATH) -type f -name "*.c" ! -name "main.c" ! -name "tests.c")
CORE_OBJ := $(patsubst %.c, $(BUILD_PATH)/%.o, $(CORE_SRC))

MAIN_SRC := $(SRC_PATH)/main.c
MAIN_OBJ := $(patsubst %.c, $(BUILD_PATH)/%.o, $(MAIN_SRC))

TARGET := $(BIN_PATH)/editor.bin

all: $(TARGET)

$(BUILD_PATH)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(COMPILATION_FLAGS) $< -o $@

$(TARGET): $(MAIN_OBJ) $(CORE_OBJ)
	$(CC) $^ $(LINKER_FLAGS) -o $@

run: $(TARGET)
	./$<

clean:
	rm -rf $(BUILD_PATH)/* $(BIN_PATH)/*
