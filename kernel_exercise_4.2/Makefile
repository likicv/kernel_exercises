# Makefile

# Target executable
TARGET = hello

# Source file
SRC = hello.s

# Object file
OBJ = $(SRC:.s=.o)

# Default rule: build the executable
all: $(TARGET)

# Build the executable from object file
$(TARGET): $(OBJ)
	ld -o $@ $^

# Assemble the source file into object
%.o: %.s
	as -o $@ $<

# Clean up generated files
clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
