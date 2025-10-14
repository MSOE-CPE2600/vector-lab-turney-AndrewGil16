# Compiler and Flags
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Target 
TARGET = lab5

# Object files
OBJS = lab5main.o lab5controller.o

# Default rule
all: $(TARGET)

# Link obj files
$(TARGET) : $(OBJS)
	$(CC)	$(CFLAGS)  -o $(TARGET) $(OBJS)

# Compile .c
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean files
clean:
	rm -f $(OBJS)	$(TARGET)

# Run
run: $(TARGET)
	./$(TARGET)