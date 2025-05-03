build/hello: build/hello.o
	ld build/hello.o -o build/hello

build/hello.o: hello.s
	mkdir -p build/
	as hello.s -o build/hello.o

clean: 
	rm build/* -r

run: build/hello
	./build/hello
