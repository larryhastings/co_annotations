from dataclasses import dataclass

@dataclass
class Foo:
    pass

@dataclass
class Bar:
    foo: Foo