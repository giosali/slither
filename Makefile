NAME=slither
OUTPUT_NAME=out

clean:
	@rm -rf $(OUTPUT_NAME)
	@rm -rf $(OUTPUT_NAME)_test

build:
	@cmake -B $(OUTPUT_NAME) -S . -G Ninja
	@cmake --build $(OUTPUT_NAME) -j 4

run:
	@sudo ./$(OUTPUT_NAME)/$(NAME) --verbose

tests:
	@cmake -B $(OUTPUT_NAME)_test -S ./test/
	@cmake --build $(OUTPUT_NAME)_test
	./$(OUTPUT_NAME)_test/$(NAME)_test