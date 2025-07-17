
CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -MMD

BIN := loadbalancer
SRCS := main.cpp
OBJS := $(SRCS:.cpp=.o)

all: $(BIN)


$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BIN) $(OBJS) *.d
