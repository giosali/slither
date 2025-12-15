NAME=slither
OUTPUT_NAME=build

.PHONY: build
build:
	@cmake -B $(OUTPUT_NAME) -S . -G Ninja
	@cmake --build $(OUTPUT_NAME) -j 4

.PHONY: test
test:
	@cmake -B $(OUTPUT_NAME)_test -S ./test/
	@cmake --build $(OUTPUT_NAME)_test
	./$(OUTPUT_NAME)_test/$(NAME)_test
