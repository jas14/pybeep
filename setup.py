#!/usr/bin/env python

from distutils.core import setup, Extension

setup(
    ext_modules=[Extension("_pybeep", ["_pybeep.c", "pybeep.c"])]
)
