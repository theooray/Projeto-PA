CXX = g++
CXXFLAGS = -O2 -Iinclude -Wall -std=c++17
LDFLAGS = -static -static-libgcc -static-libstdc++

ifeq ($(OS),Windows_NT)
    SHELL = cmd.exe
    RM = del /f /q
    MKDIR = if not exist obj mkdir obj
    TARGET_EXT = .exe
    FIXPATH = $(subst /,\,$1)
else
    RM = rm -f
    MKDIR = mkdir -p obj
    TARGET_EXT =
    FIXPATH = $1
endif

TARGET = programa$(TARGET_EXT)
SRCS = main.cpp $(wildcard src/*.cpp)
OBJS = $(addprefix obj/,$(notdir $(SRCS:.cpp=.o)))
INCL = $(wildcard include/*.hpp)

VPATH = src

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(LDFLAGS) -o $@ $^

obj/%.o: %.cpp $(INCL) | obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

obj:
	$(MKDIR)

clean:
	$(RM) $(call FIXPATH,$(OBJS)) $(TARGET)