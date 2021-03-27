// Implementation of PEP 649
#ifndef Py_ANNOTATIONNAMEOBJECT_H
#define Py_ANNOTATIONNAMEOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

PyAPI_FUNC(PyObject *) Py_AnnotationName(PyObject *);
PyAPI_DATA(PyTypeObject) Py_AnnotationNameType;

#ifdef __cplusplus
}
#endif
#endif /* !Py_ANNOTATIONNAMEOBJECT_H */
