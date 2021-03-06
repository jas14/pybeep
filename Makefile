SRC=pybeep.c pybeep.h _pybeep.c

.PHONY: all clean inplace
all: inplace

pybeep.so: $(SRC)
	python3 setup.py build_ext --inplace

inplace: pybeep.so

build: $(SRC)
	python3 setup.py build_ext

clean:
	rm -rf *.so build
