NAME=slither

clean:
	@rm -rf build

build: clean
	@cmake -B build -S .
	@cmake --build build

run:
	@./build/$(NAME)