NAME=slither
OUTPUT_NAME=out

clean:
	@rm -rf $(OUTPUT_NAME)
	@rm -rf $(OUTPUT_NAME)_test

build:
	@cmake -B $(OUTPUT_NAME) -S . -G Ninja
	@cmake --build $(OUTPUT_NAME) -j 4

run:
	@test -z "$(getcap ./$(OUTPUT_NAME)/$(NAME))" && sudo setcap cap_dac_override=ep ./$(OUTPUT_NAME)/$(NAME)
	./$(OUTPUT_NAME)/$(NAME) --verbose

tests:
	@cmake -B $(OUTPUT_NAME)_test -S ./test/
	@cmake --build $(OUTPUT_NAME)_test
	./$(OUTPUT_NAME)_test/$(NAME)_test