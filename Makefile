BUILD_DIR = build

all: $(BUILD_DIR)/Makefile
	cmake --build $(BUILD_DIR)

$(BUILD_DIR)/Makefile:
	cmake -S . -B $(BUILD_DIR)

clean:
	$(MAKE) -C $(BUILD_DIR) clean
	rm -rf $(BUILD_DIR)

.PHONY: all clean