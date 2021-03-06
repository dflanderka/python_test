import sys

import numpy as np
import flowpy

def test_add():
    x = 2
    y = 3
    res = flowpy.add(x,y)
    print(res)
    
def test_example():
    o = flowpy.PythonFieldBase()
    o.t = 0.1
    print(o.t)
    o.set_result("result", 1, 3, 16)
    o.add_to_dict("csection", 1, 1, 16)
    o.add_to_dict("velocity", 1, 3, 16)
    o.print_fields()

test_add()
test_example()
