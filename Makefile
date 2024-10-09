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
	$(ARDUINO_CLI) compile --fqbn $(BOARD_TAG) --output-dir $(BUILD_DIR) src/$(SKETCH)

# Upload the sketch
upload:
	$(ARDUINO_CLI) upload -p $(PORT) --fqbn $(BOARD_TAG) -i $(BUILD_DIR)/$(SKETCH).hex

# Clean the build directory
clean:
	rm -rf $(BUILD_DIR)

TEST_OBJS = build/aqi.o build/battery.o build/test/aqi_test.o build/test/battery_test.o build/test/mock_arduino.o build/test/catch/catch_amalgamated.o

build/test/catch/%.o: build/test/catch/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

build/test/%.o: src/test/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@ -Isrc/test/catch -Isrc/

build/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: prep $(TEST_OBJS)
	g++ -o build/runner $(TEST_OBJS)
	./build/runner

.PHONY: all compile upload clean prep