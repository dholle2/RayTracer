CC := g++
CFLAGS := -Wall -g
TARGET := render

# $(wildcard *.cpp /xxx/xxx/*.cpp): get all .cpp files from the current directory and dir "/xxx/xxx/"
SRCS := $(wildcard *.cpp /Utilities/*.cpp /SceneObjects/*.cpp /Misc./*.cpp)
# $(patsubst %.cpp,%.o,$(SRCS)): substitute all ".cpp" file name strings to ".o" file name strings
OBJS := $(patsubst %.cpp,%.o,$(SRCS))

all: $(TARGET)
$(TARGET): $(OBJS)
	$(CC) -o $(CC)$@ $^

%.o: %.cpp
	$(CC) $(CFLAGS) -c $<
clean:
	rm -rf $(TARGET) *.o

.PHONY: all clean

#	OBJ_DIR := .../obj
#	SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
#	OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
#	LDFLAGS := ...
#	CPPFLAGS := ...
#	CXXFLAGS := ...

#	main.exe: $(OBJ_FILES)
#	   g++ $(LDFLAGS) -o $@ $^

#	$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
#	   g++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
