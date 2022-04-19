import sys

import pytest
import py_field_base
import numpy as np

def test_py_field_base():
    used_fields = ["cross_section", "velocity", "init_conc"]
    field=py_field_base.PythonFieldBase(used_fields)
    time = field.set_time(0.5)
    assert time == 0.5
    dep_list = field.set_dependency()
    assert used_fields == dep_list
