CXX := g++
CXXFLAGS := -std=c++17 -I"C:/vcpkg/installed/x64-windows/include" -Iinclude   # Ensure path to curl headers
# LDFLAGS :=  -L"C:/vcpkg/installed/x64-windows/lib"
LIBS := -lcurl

SRC := src/main.cpp src/api_client.cpp #src/websocket_client.cpp
TARGET = trading_system

# # Dependency files generated by g++
# DEPS := $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(LIBS)

# # Rule to compile .cpp files into .o files and generate .d dependency files
# %.o: %.cpp
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# # Include automatically generated dependency files
# -include $(DEPS)

clean:
	rm -f $(TARGET)

.PHONY: all clean
