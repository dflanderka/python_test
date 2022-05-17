import sys

import numpy as np
import flowpy


class UserContext:
    coef = 0
    
    def __init__(self, c):
        self.coef = c

    def mult(self, val):
        return self.coef * val


def fn_init(obj: flowpy.PythonFieldBase) -> UserContext:
    user_context = UserContext(obj.t)
    return user_context


def fn_reinit(obj: flowpy.PythonFieldBase, user_context: UserContext) -> flowpy.PythonFieldBase:
    obj.set_result("result", 1, 3, 16)
    obj.add_to_dict("csection", 1, 1, 16)
    obj.add_to_dict("velocity", 1, 3, 16)
    obj.print_fields()
    return obj


def fn_eval(obj: flowpy.PythonFieldBase, user_context: UserContext):
    multi = user_context.mult(5)
    velocity_field = obj.f_dict["velocity"]
    obj.result = velocity_field * 2


def test():
    print("Calling func example:")
    field = flowpy.PythonFieldBase()
    field.t = 0.1
    uc = fn_init(field)
    multi = uc.mult(2)
    print(multi)
    fn_reinit(field, uc)
    field.print_fields()
    fn_eval(field, uc)
    field.print_result()
  
test()