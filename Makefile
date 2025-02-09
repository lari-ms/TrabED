# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Iinclude

# Source files
SRCS = src/bd_paciente.c src/main.c src/paciente.c src/utils.c src/arquivo.c

# Object files
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = paciente

.PHONY: all compile run clean

# Default target (compile and run)
all: compile run

# Explicit compile target (produces the target program)
compile: $(TARGET)

# Run the executable
run: $(TARGET)
	./$(TARGET)

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)

# Compile source files into object files
src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)
