# compiler and flags
CXX = g++
CXXFLAGS = -Wall -g

INC = -I./include

# directories
SRC_DIR = src
OUT_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
BIN = $(OUT_DIR)/main.exe

.PHONY: all run clean

all: $(BIN)

$(BIN): $(SRCS) | $(OUT_DIR)
	$(CXX) $(INC) $^ -o $@

$(OUT_DIR):
	mkdir -p $(OUT_DIR)

run: $(BIN)
	./$(BIN)

clean:
	rm -rf $(OUT_DIR)