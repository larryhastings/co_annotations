#include "Python.h"
#include "pycore_object.h"
#include "structmember.h"

typedef struct {
	PyObject_HEAD
	PyObject *name;
} annotnameobject;

static void
an_dealloc(PyObject *self)
{
	annotnameobject *alias = (annotnameobject *)self;

	_PyObject_GC_UNTRACK(self);
	Py_XDECREF(alias->name);
	Py_TYPE(self)->tp_free(self);
}

static int
an_traverse(PyObject *self, visitproc visit, void *arg)
{
    annotnameobject *alias = (annotnameobject *)self;
    Py_VISIT(alias->name);
    return 0;
}

static PyObject *
an_repr(PyObject *self)
{
    annotnameobject *alias = (annotnameobject *)self;

    _PyUnicodeWriter writer;
    _PyUnicodeWriter_Init(&writer);

    if (_PyUnicodeWriter_WriteASCIIString(&writer, "<unresolved name: ", 18) < 0) {
        goto error;
    }
    if (_PyUnicodeWriter_WriteStr(&writer, alias->name) < 0) {
        goto error;
    }
    if (_PyUnicodeWriter_WriteASCIIString(&writer, ">", 1) < 0) {
        goto error;
    }
    return _PyUnicodeWriter_Finish(&writer);
error:
    _PyUnicodeWriter_Dealloc(&writer);
    return NULL;
}

static Py_hash_t
an_hash(PyObject *self)
{
    annotnameobject *alias = (annotnameobject *)self;
    return PyObject_Hash(alias->name);
}

static PyObject *
an_richcompare(PyObject *a, PyObject *b, int op)
{
    if (!Py_IS_TYPE(a, &Py_AnnotationNameType) ||
        !Py_IS_TYPE(b, &Py_AnnotationNameType))
    {
        Py_RETURN_NOTIMPLEMENTED;
    }
    annotnameobject *aa = (annotnameobject *)a;
    annotnameobject *bb = (annotnameobject *)b;
    return PyObject_RichCompare(aa->name, bb->name, op);
}

static PyObject *
an_reduce(PyObject *self, PyObject *Py_UNUSED(ignored))
{
    annotnameobject *alias = (annotnameobject *)self;
    return Py_BuildValue("O(O)", Py_TYPE(alias),
                         alias->name);
}

static PyMethodDef an_methods[] = {
    {"__reduce__", an_reduce, METH_NOARGS},
    {0}
};

static PyMemberDef an_members[] = {
    {"__name__", T_OBJECT, offsetof(annotnameobject, name), READONLY},
    {0}
};

static PyObject *
an_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    if (!_PyArg_NoKwnames("AnnotationName", kwds)) {
        return NULL;
    }
    if (!_PyArg_CheckPositional("AnnotationName", PyTuple_GET_SIZE(args), 1, 1)) {
        return NULL;
    }
    PyObject *name = PyTuple_GET_ITEM(args, 0);
    if (!PyUnicode_Check(name)) {
        PyErr_SetString(PyExc_TypeError, "name must be a string");
        return NULL;
    }
    return Py_AnnotationName(name);
}

PyTypeObject Py_AnnotationNameType = {
    PyVarObject_HEAD_INIT(&PyType_Type, 0)
    .tp_name = "types.AnnotationName",
    .tp_doc = "Represent a name in a type annotation",
    .tp_basicsize = sizeof(annotnameobject),
    .tp_dealloc = an_dealloc,
    .tp_repr = an_repr,
    .tp_hash = an_hash,
    .tp_flags = Py_TPFLAGS_DEFAULT | Py_TPFLAGS_HAVE_GC,
    .tp_traverse = an_traverse,
    .tp_richcompare = an_richcompare,
    .tp_methods = an_methods,
    .tp_members = an_members,
    .tp_alloc = PyType_GenericAlloc,
    .tp_new = an_new,
    .tp_free = PyObject_GC_Del,
};

PyObject *
Py_AnnotationName(PyObject *name)
{
    annotnameobject *alias = PyObject_GC_New(annotnameobject, &Py_AnnotationNameType);
    if (alias == NULL) {
        return NULL;
    }

    Py_INCREF(name);
    alias->name = name;
    _PyObject_GC_TRACK(alias);
    return (PyObject *)alias;
}
