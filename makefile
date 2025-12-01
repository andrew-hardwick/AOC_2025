all: build
	meson install -C build

build:
	meson setup build

clean:
	rm -rf build
	rm -rf result

