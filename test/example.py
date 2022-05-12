import sys

import numpy as np
import myexample

def test_example():
    o = myexample.ExampleBase()
    o.t = 0.1
    print(o.t)
    o.set_result(1, 3, 16)
    o.add_to_dict("csection", 1, 1, 16)
    o.add_to_dict("velocity", 1, 3, 16)
    o.print_fields()

test_example()