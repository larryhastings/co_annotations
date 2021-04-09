from __future__ import co_annotations

m_int:int=3
m_str:str=b"foo"
m_MyType:MyType=None

def fn(fn_int:int=3, fn_str:str="foo", fn_MyType:MyType=None):
    pass

class MyType:
    kls_int:int=3
    kls_str:str="foo"
    kls_MyType:MyType=None


class Nested:
    alias = int
    def f(self, x: alias):
        pass

def closure_and_classvars():
    a4 = "a4"
    class C:
        a1 = "a1"
        a2 = "a2"
        a3 = "a3"
        def method1(self, p1:a1): pass
        def method2(self, p2:a2): pass
        def method3(self, p3:a3): pass
        def method4(self, p4:a4): pass
        def method5(self, p5:int): pass

        # evaluate these early
        x = method1.__annotations__
        y = method2.__annotations__
    return C
