CC = clang
CFLAGS = -Wall -Wextra -g -Isrc
LFLAGS = 

TARGET = editor
BUILDPATH = build

SRC = $(shell find src -type f -name "*.c" ! -name ".#*" ! -name "*~")
OBJ = $(patsubst %.c, $(BUILDPATH)/%.o, $(SRC))

.PHONY: all run clean

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LFLAGS) $^ -o $@

$(BUILDPATH)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$<

clean: 
	rm -rf $(TARGET) $(BUILDPATH)
