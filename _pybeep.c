#include <Python.h>
#include "pybeep.h"

/*
 * Module stuff for pybeep.
 */

static char beep_docstring[] =
    "Beep, optionally at a certain frequency and/or with specific duration.";

static PyMethodDef module_methods[] = {
    {"beep", pybeep_beep, METH_NOARGS, beep_docstring},
    {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
init_pybeep(void)
{
    Py_InitModule("_pybeep", module_methods);
}

