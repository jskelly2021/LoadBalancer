
CXX := g++
CXXFLAGS := -std=c++23 -Wall -Wextra -MMD

SRC_DIR := src
BUILD_DIR := build

BIN := $(BUILD_DIR)/loadbalancer
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS :=  $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

-include $(OBJS:.o=.d)

.PHONY: all run clean

all: $(BUILD_DIR) | $(BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


run: $(BIN)
	./$(BIN)


clean:
	rm -rf $(BUILD_DIR)
