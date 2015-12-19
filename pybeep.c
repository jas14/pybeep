#include <Python.h>
#include "pybeep.h"

PyObject *
pybeep_beep(PyObject *self, PyObject *args)
{
    printf("\a");
    Py_RETURN_NONE;
}
