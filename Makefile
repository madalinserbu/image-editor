
CFLAGS=-Wall -Wextra -std=c99

build:
	gcc $(CFLAGS) -o image_editor image_editor.c -lm
run:
	./image_editor
clean:
	rm -r image_editor
