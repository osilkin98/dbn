SRC_DIR := src
BUILD_DIR := build
TEST_DIR := test

CXXFLAGS = -std=c++14 -Wall -Wextra -O2
LDLIBS = -lgmp -lgmpxx -lsodium -I$(SRC_DIR)

TESTS = $(BUILD_DIR)/hash_prime_test

default: compile
compile: $(BUILD_DIR) $(TESTS)

debug: CXXFLAGS += -g
debug: compile

clean: $(BUILD_DIR)
	rm -rf $(BUILD_DIR)/*

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $< $(LDLIBS) -o $@

$(BUILD_DIR)/%_test.o: $(TEST_DIR)/%_test.cpp
	$(CXX) -c $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $< $(LDLIBS) -o $@

$(BUILD_DIR)/%_test: $(BUILD_DIR)/%_test.o $(BUILD_DIR)/database.o $(BUILD_DIR)/hash.o
	$(CXX) $(CFLAGS) $(CPPFLAGS) $(CXXFLAGS) $^ $(LDLIBS) -o $@
