# Define the board and port
BOARD_TAG = esp32:esp32:esp32s3
PORT = /dev/ttyACM0

# Define the sketch file
SKETCH = src.ino

# Define the output directory
BUILD_DIR = build

# Define the arduino-cli command
ARDUINO_CLI = arduino-cli

# Default target
all: prep compile upload

prep:
	mkdir -p build/test/catch

# Compile the sketch
compile:
	$(ARDUINO_CLI) compile --fqbn $(BOARD_TAG) --output-dir $(BUILD_DIR) src/$(SKETCH) --build-property "build.extra_flags=-Iinclude/ -DESP32"

# Upload the sketch
upload:
	$(ARDUINO_CLI) upload -p $(PORT) --fqbn $(BOARD_TAG) -i $(BUILD_DIR)/$(SKETCH).hex

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR)

# Source files
TEST_SRCS := $(wildcard test/*_test.cpp)

# Object files
APP_OBJS = build/aqi.o build/battery.o
TEST_OBJS = $(patsubst test/%.cpp,build/%.o,$(TEST_SRCS))
TEST_LIB_OBJS = build/test/mock_arduino.o build/test/catch/catch_amalgamated.o

build/test/catch/%.o: test/catch/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/test/mock_arduino.o: test/mock/mock_arduino.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/%_test.o: test/%_test.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -Itest/catch -Iinclude/ -Itest/

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -Iinclude/ -Itest/

test: prep $(APP_OBJS) $(TEST_OBJS) $(TEST_LIB_OBJS)
	g++ -o build/runner $(APP_OBJS) $(TEST_OBJS) $(TEST_LIB_OBJS)
	./build/runner

.PHONY: all compile upload clean prep test