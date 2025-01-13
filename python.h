#include <Python.h>

#define PY_DEF_END {NULL, NULL, 0, NULL}
#define PY_DEF(FNAME, doc) {#FNAME, FNAME, METH_VARARGS, doc}

#define PY_FUNCTION(FNAME) PyObject *FNAME(PyObject *self, PyObject *args)

#define PY_MODULE(mname, doc, functions)                                       \
    {PyModuleDef_HEAD_INIT, #mname, #doc, -1, functions}

/** Example

// src.c
#include "python.h"

PY_FUNCTION(sum);

static PyMethodDef functions[] = {
    PY_DEF(sum, "Sums numbers in range [1, arg]."),
    PY_DEF_END};

static PyModuleDef module = PY_MODULE("c_lib", "<Documentation>", functions);

PyMODINIT_FUNC PyInit_c_lib() {
    return PyModule_Create(&module);
}

PY_FUNCTION(sum) {
    long stop;

    if (!PyArg_ParseTuple(args, "l", &stop))
    {
        return NULL;
    }

    long s = 0;
    for (int i = 1; i <= stop; ++i)
    {
        s += i;
    }

    return PyLong_FromLong(s);
}

// setup.py
from setuptools import Extension, setup

setup(
    name='py_lib',
    ext_modules=[
        Extension(
            name='c_lib',
            sources=['src.c'],
            extra_compile_args=['/Wall'],
            extra_compile_args=['-Wall', '-Wextra', '-Wpedantic'],
        )
    ]
)
 */
