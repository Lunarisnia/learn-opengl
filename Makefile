run:
	# Solution to linking found here: https://stackoverflow.com/questions/73142912/glfw-undefined-symbols-for-architecture-arm64
	clang++ ./main.cpp -I/usr/local/include -L/usr/local/lib -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -o debug
	./debug

