NAME=slither

clean:
	@rm -rf build

build: clean
	@cmake -B build -S .
	@cmake --build build

run:
	@sudo ./build/$(NAME)

tests:
	@g++ ./test/main.cpp -std=c++20 -o ./test/a.out
	@./test/a.out
	@rm ./test/a.out