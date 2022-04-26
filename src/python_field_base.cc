/*
 * python_field_base.cc
 */

#include <pybind11/pybind11.h>
//#include <pybind11/numpy.h>
#include <pybind11/stl.h>
#include "python_field_base.hh"

namespace py = pybind11;
using namespace std;



//std::vector<unsigned int> tree_find_box(BIHTree *tree, BoundingBox &box, bool full_list) {
//    std::vector<unsigned int> result;
//    tree->find_bounding_box(box, result, full_list);
//    return result;
//}


// TODO: use PYBIND11_MODULE
PYBIND11_MODULE(py_field_base, m) {
//    //py::module m( "bih", );
    m.doc() = "PythonFieldBase.";
    py::class_<PythonFieldBase>(m, "FieldPython")
		.def_property("time", &PythonFieldBase::get_time, &PythonFieldBase::set_time)
        .def("get_dependency", &PythonFieldBase::get_dependency)
        .def("cache_reinit", &PythonFieldBase::cache_reinit , py::return_value_policy::copy);

//    py::class_<BIHTree>(m, "BIH")
//        .def(py::init<unsigned int>(), py::arg("soft_leaf_size_limit")  = 20)
//        .def("add_boxes", &BIHTree::add_boxes)
//        .def("construct", &BIHTree::construct)
//        .def("find_box", &tree_find_box,
//                 py::arg("box"),  py::arg("full_list") = false)
//        .def("find_point", &tree_find_point,
//                 py::arg("point"),  py::arg("full_list") = false);
    //return m.ptr();

}

