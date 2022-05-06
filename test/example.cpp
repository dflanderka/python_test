/**
 * Simple test.
 */


#include <pybind11/pybind11.h>
#include "example.hh"

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(myexample, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring
    m.def("add", &add, "A function that adds two numbers");

    py::class_<ExampleBase>(m, "ExampleBase")
        .def(py::init<>())
        //.def(py::init<std::string, std::vector<ssize_t>, std::vector<double>>())
        .def("set_result", &ExampleBase::set_result)
		.def("add_to_dict", &ExampleBase::add_to_dict)
		.def("print_fields", &ExampleBase::print_fields)
        .def_property("t", &ExampleBase::get_time, &ExampleBase::set_time);

}

//int main() {
//	int a = 1;
//	int b = 2;
//	int c = add(a, b);
//	std::cout << "Add function: " << a << " + " << b << " = " << c << std::endl;
//	return 0;
//}
