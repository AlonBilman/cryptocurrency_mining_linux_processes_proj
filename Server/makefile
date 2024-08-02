# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17
LDFLAGS = -lz

# Source and header files
SRCS = block.cpp global.cpp main.cpp server.cpp
HDRS = block.h global.h server.h

# Output executable
TARGET = mtacoin_server_app

# Default target
all: $(TARGET)

# Linking
$(TARGET): $(SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS) $(LDFLAGS)

# Clean up
clean:
	rm -f $(TARGET) *.o