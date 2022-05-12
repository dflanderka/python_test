import sys

import numpy as np
import myexample

class Field(myexample.ExampleBase):
    pass
  
    def __call__(self):
        print("Calling call")
        velocity_field = self.f_dict["velocity"]
        self.result = velocity_field * 2
    
def test():
    print("Calling test")
    field = Field()
    field.t = 0.1
    print(field.t)
    field.set_result(1, 3, 16)
    field.add_to_dict("csection", 1, 1, 16)
    field.add_to_dict("velocity", 1, 3, 16)
    field.print_fields()
    field()
    field.print_result()
  
test()
