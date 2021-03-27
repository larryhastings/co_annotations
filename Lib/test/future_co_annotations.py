from __future__ import co_annotations

m_int:int=3
m_str:str=b"foo"
m_MyType:MyType=None
m_undef:undef=None

def fn(fn_int:int=3, fn_str:str="foo", fn_MyType:MyType=None, fn_undef:undef=None):
    pass

class MyType:
    kls_int:int=3
    kls_str:str="foo"
    kls_MyType:MyType=None
    kls_undef:undef=None
