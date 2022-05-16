/**
 * Simple test.
 */


#include <pybind11/pybind11.h>
#include <pybind11/embed.h>    // everything needed for embedding
#include <pybind11/stl.h>      // type conversion
#include "example.hh"

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(flowpy, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring
    m.def("add", &add, "A function that adds two numbers");

    py::class_<FieldPythonBase>(m, "FieldPythonBase")
        .def(py::init<>())
        //.def(py::init<std::string, std::vector<ssize_t>, std::vector<double>>())
        .def("set_result", &FieldPythonBase::set_result)
		.def("add_to_dict", &FieldPythonBase::add_to_dict)
        .def("set_result_data", &FieldPythonBase::set_result_data)
		.def("add_to_dict_data", &FieldPythonBase::add_to_dict_data)
		.def("print_fields", &FieldPythonBase::print_fields)
		.def("print_result", &FieldPythonBase::print_result)
        .def_property("t", &FieldPythonBase::get_time, &FieldPythonBase::set_time)
	    .def_property("result", &FieldPythonBase::get_field_result, &FieldPythonBase::set_field_result)
	    .def_property("f_dict", &FieldPythonBase::get_fields_dict, &FieldPythonBase::set_fields_dict);

}

void fill_vec(std::vector<double> &vec) {
	for (uint i=0; i<vec.size(); ++i) vec[i] = 1.0 + i;
}

int main() {
	py::scoped_interpreter guard{}; // start the interpreter and keep it alive

	// test of simple function in C++
	int a = 1;
	int b = 2;
	int c = add(a, b);
	std::cout << "Add function: " << a << " + " << b << " = " << c << std::endl;

	// test of FieldPythonBase object in C++
	std::vector<double> csection_vec(16);
	fill_vec(csection_vec);
	std::vector<ssize_t> csection_shape = {1,1};
	std::vector<double> velocity_vec(48);
	fill_vec(velocity_vec);
	std::vector<ssize_t> velocity_shape = {1,3};
	std::vector<double> result_vec(48);
	fill_vec(result_vec);
	std::vector<ssize_t> result_shape = {1,3};
	std::vector<FieldCacheProxy> field_data;
	field_data.emplace_back("csection", csection_shape, csection_vec);
	field_data.emplace_back("velocity", velocity_shape, velocity_vec);
	FieldCacheProxy result_data("result", result_shape, result_vec);
	FieldPythonBase field(field_data, result_data);
	field.print_fields();

	// test of call of simple function in Python
	// source: https://stackoverflow.com/questions/42521830/call-a-python-function-from-c-using-pybind11
	auto math = py::module::import("math");
	double root_two = math.attr("sqrt")(2.0).cast<double>();
	std::cout << "The square root of 2 is: " << root_two << "\n";

	// test of call of 'add' function in Python
	// source: same as previous
	auto flowpy = py::module::import("flowpy");
    py::function add_func =
        py::reinterpret_borrow<py::function>(   // cast from 'object' to 'function - use `borrow` (copy) or `steal` (move)
            py::module::import("flowpy").attr("add")  // import method "min_rosen" from python "module"
        );
	int add_result = add_func(2, 3).cast<int>();
	std::cout << "Result of add(2, 3) is: " << add_result << "\n";

	return 0;
}
