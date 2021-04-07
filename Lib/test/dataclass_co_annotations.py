from __future__ import co_annotations
from dataclasses import dataclass

@dataclass
class Bar:
    foo: Foo

@dataclass
class Foo:
    pass
