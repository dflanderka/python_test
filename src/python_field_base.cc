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
		.def(py::init<std::vector<FieldCacheProxy> &, FieldCacheProxy &>())
		.def_property("time", &PythonFieldBase::get_time, &PythonFieldBase::set_time)
//        .def("get_dependency", &PythonFieldBase::get_dependency)
        .def("cache_reinit", &PythonFieldBase::cache_reinit , py::return_value_policy::copy);

    py::class_<FieldCacheProxy>(m, "FieldCacheProxy")
        .def(py::init<std::string, std::vector<ssize_t>, std::vector<double>>())
        .def("field_name", &FieldCacheProxy::field_name)
        .def("shape", &FieldCacheProxy::shape)
        .def("field_cache_ptr", &FieldCacheProxy::field_cache_ptr);
    //return m.ptr();

}

