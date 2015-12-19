SRC=pybeep.c pybeep.h _pybeep.c

.PHONY: all clean inplace
all: inplace

pybeep.so: $(SRC)
	python setup.py build_ext --inplace

inplace: pybeep.so

build: $(SRC)
	python setup.py build_ext

clean:
	rm -rf pybeep.so build
