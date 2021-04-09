#include <Python.h>
#include "pybeep.h"

/*
 * Module stuff for pybeep.
 */

static char beep_docstring[] =
    "Beep, optionally at a certain frequency and/or with specific duration.";

static PyMethodDef module_methods[] = {
    {"beep", (PyCFunction) pybeep_beep, METH_VARARGS, beep_docstring},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pybeep =
{
    PyModuleDef_HEAD_INIT,
    "pybeep", /* name of module */
    "usage: do_beep(freq)\n", /* module documentation, may be NULL */
    -1,   /* size of per-interpreter state of the module, or -1 if the module keeps state in global variables. */
    module_methods
};

PyMODINIT_FUNC PyInit_pybeep(void)
{
    return PyModule_Create(&pybeep);
}
