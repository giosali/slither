NAME=slither

build:
	@cmake -B build -S .
	@cmake --build build

clean:
	@rm -rf build

run:
	@./build/$(NAME)