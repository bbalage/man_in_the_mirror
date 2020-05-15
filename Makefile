all:
	gcc -Iinclude/ src/callbacks.c src/camera.c src/init.c src/main.c src/scene.c src/texture.c src/utils.c src/man.c src/objects.c -lSOIL -lobj -lopengl32 -lglu32 -lglut32 -lm -o man_in_the_mirror.exe -Wall -Wextra -Wpedantic

linux:
	gcc -Iinclude/ src/callbacks.c src/camera.c src/init.c src/main.c src/scene.c src/texture.c src/utils.c src/man.c src/objects.c -lSOIL -lobj -lGL -lGLU -lglut -lm -o man_in_the_mirror -Wall -Wextra -Wpedantic
