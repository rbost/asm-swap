CPPFLAGS ?= -I.
CXXFLAGS ?= -std=c++11
BUILD_DIR ?= ./build
SRC_DIR ?= ./src
LDFLAGS ?= -lpthread

test: $(BUILD_DIR)/main.o $(BUILD_DIR)/gtest.o $(BUILD_DIR)/swap.o
	$(CXX) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/swap.h
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/gtest.o: gtest/gtest-all.cc
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/swap.o: $(SRC_DIR)/swap.c $(SRC_DIR)/swap.h
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@



# TARGET_EXEC ?= test
#
# BUILD_DIR ?= ./build
# SRC_DIRS ?= ./src
#
# SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
# OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
# DEPS := $(OBJS:.o=.d)
#
# INC_DIRS := $(shell find $(SRC_DIRS) -type d)
# INC_FLAGS := $(addprefix -I,$(INC_DIRS))
#
# CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -I.
# CXXFLAGS ?= -std=c++11
#
# $(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
# 	$(CC) $(OBJS) -o $@ $(LDFLAGS)
#
# # assembly
# $(BUILD_DIR)/%.s.o: %.s
# 	$(MKDIR_P) $(dir $@)
# 	$(AS) $(ASFLAGS) -c $< -o $@
#
# # c source
# $(BUILD_DIR)/%.c.o: %.c
# 	$(MKDIR_P) $(dir $@)
# 	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@
#
# # c++ source
# $(BUILD_DIR)/%.cpp.o: %.cpp
# 	$(MKDIR_P) $(dir $@)
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@
#
#
.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)
#
# -include $(DEPS)
#
MKDIR_P ?= mkdir -p