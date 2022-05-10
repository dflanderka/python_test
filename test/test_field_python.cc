/*
 * test_field_python.cc
 *
 *  Created on: Apr 26, 2022
 *      Author: David Flanderka
 */




/*
 * NOTE: This unit test uses asserts defined in namespace feal, not asseerts defined
 * in gtest library.
 */

#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <pybind11/embed.h> // everything needed for embedding

#include "python_field_base.hh"


void test_base_class() {
    uint vec_size = 24;

    std::vector<ssize_t> shape_scalar = {1};
    std::vector<ssize_t> shape_vector = {3, 1};
    std::vector<double> field_vector_cache(3*vec_size);
    std::vector<double> field_scalar_cache(vec_size);
    std::vector<double> field_result_cache(3*vec_size);

    FieldCacheProxy result_cache_data("result", shape_vector, field_result_cache);
    std::vector<FieldCacheProxy> input_fields_data;
    input_fields_data.emplace_back("vector_field", shape_vector, field_vector_cache);
    input_fields_data.emplace_back("scalar_field", shape_scalar, field_scalar_cache);

    PythonFieldBase python_base(input_fields_data, result_cache_data);
    double time = 0.5;
    python_base.set_time(time);
    std::cout << "PythonFieldBase time is: " << python_base.get_time() << std::endl;
    std::cout << "Dictionary contains fields: ";
    for (auto item : python_base.cache_reinit())
    {
    	std::cout << item.first << ", ";
    }
    std::cout << std::endl;
}

//void test_bih_tree() {
//
//}

int main() {
	py::scoped_interpreter guard{}; // start the interpreter and keep it alive
	std::cout << "Start python test \n";
	test_base_class();
//    test_bih_tree();

}
