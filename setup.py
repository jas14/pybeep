#!/usr/bin/env python

from distutils.core import setup, Extension

setup(
    name='pybeep',
    version='0.1',
    ext_modules=[Extension("pybeep", ["_pybeep.c", "pybeep.c"])]
)
