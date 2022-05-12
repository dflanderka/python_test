/**
 * Simple test.
 */


#include <pybind11/pybind11.h>
#include <pybind11/embed.h> // everything needed for embedding
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

	int a = 1;
	int b = 2;
	int c = add(a, b);
	std::cout << "Add function: " << a << " + " << b << " = " << c << std::endl;

	std::vector<double> csection_vec(16);
	fill_vec(csection_vec);
	std::vector<double> velocity_vec(48);
	fill_vec(velocity_vec);
	std::vector<double> result_vec(48);
	fill_vec(result_vec);
	FieldPythonBase field;
	field.add_to_dict_data( "csection", &(csection_vec[0]), 1, 1, 16 );
	field.add_to_dict_data( "velocity", &(velocity_vec[0]), 1, 3, 16 );
	field.set_result_data( &(result_vec[0]), 1, 3, 16 );
	field.print_fields();

	return 0;
}
