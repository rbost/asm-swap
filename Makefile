CPPFLAGS ?= -I. -mavx -pthread
CXXFLAGS ?= -std=c++11
BUILD_DIR ?= ./build
SRC_DIR ?= ./src
LDFLAGS ?= -lpthread

test: $(BUILD_DIR)/main.o $(BUILD_DIR)/gtest.o $(BUILD_DIR)/swap.o
	$(CXX) $^ -o $@ $(LDFLAGS)

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/swap.h
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/gtest.o: gtest/gtest-all.cc
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/swap.o: $(SRC_DIR)/swap.c $(SRC_DIR)/swap.h
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@


.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

MKDIR_P ?= mkdir -p
