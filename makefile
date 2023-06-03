# Compiler
CC = g++
# Compiler flags
CFLAGS = -std=c++11 -Wall -Wextra
# Source files
SRCS = ActiveObject.cpp pipelie_st.cpp ThreadSafeQueue.cpp
# Object files
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
# Executable file
TARGET = pipeline_st

# Default target
all: $(TARGET)

# Compile source files into object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files into the executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)
