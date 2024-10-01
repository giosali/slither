NAME=slither

clean:
	@rm -rf build

build: clean
	@cmake -B build -S .
	@cmake --build build

run:
	@sudo ./build/$(NAME)

tests:
	@cmake -B test_build -S ./test/
	@cmake --build test_build
	./test_build/$(NAME)_test