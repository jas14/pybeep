#!/usr/bin/env python3

from distutils.core import setup, Extension

setup(
    name='pybeep',
    version='0.1',
    ext_modules=[Extension("pybeep", ["_pybeep.c", "pybeep.c"])],
    license="MIT",
    classifiers=[
        "License :: OSI Approved :: MIT License",
        "Operating System :: POSIX :: Linux"
    ],
    url="https://github.com/jas14/pybeep",
)
