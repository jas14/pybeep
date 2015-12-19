.PHONY: all clean
all: _pybeep.so

_pybeep.so: pybeep.c pybeep.h _pybeep.c
	python setup.py build_ext --inplace

clean:
	rm -f _pybeep.so
