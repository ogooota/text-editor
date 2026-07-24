CC = clang
CFLAGS = -Wall -Wextra -g
LFLAGS =

TARGET = editor
BUILDPATH = build

SRC = $(shell find . -name "*.c")
OBJ = $(patsubst %.c, $(BUILDPATH)/%.o, $(SRC))

.PHONY: clean

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