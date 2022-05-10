/*!
 *
﻿ * Copyright (C) 2015 Technical University of Liberec.  All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License version 3 as published by the
 * Free Software Foundation. (http://www.gnu.org/licenses/gpl-3.0.en.html)
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 *
 *
 * @file    python_field_base.hh
 * @brief
 */

#ifndef PYTHON_FIELD_BASE_HH_
#define PYTHON_FIELD_BASE_HH_

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
#include <pybind11/detail/common.h>

namespace py = pybind11;

class ExampleBase
{
protected:
    py::array create_array_with_data(double *data, ssize_t n_rows, ssize_t n_cols, ssize_t size)
    {
        ssize_t              ndim    = 2;
        std::vector<ssize_t> shape   = { n_rows*n_cols , size };
        std::vector<ssize_t> strides = { sizeof(double)*size , sizeof(double) };

        // create 2-D NumPy array
        return  py::array(py::buffer_info(
            data,                                    /* data as contiguous array  */
            sizeof(double),                          /* size of one scalar        */
            py::format_descriptor<double>::format(), /* data type                 */
            ndim,                                    /* number of dimensions      */
            shape,                                   /* shape of the matrix       */
            strides                                  /* strides for each axis     */
          ));
    }

    py::array create_array(ssize_t n_rows, ssize_t n_cols, ssize_t size)
    {
        std::vector<double> result(size*n_rows*n_cols);
        for (uint i=0; i<result.size(); ++i) result[i] = 1.0 + i;

        ssize_t              ndim    = 2;
        std::vector<ssize_t> shape   = { n_rows*n_cols , size };
        std::vector<ssize_t> strides = { sizeof(double)*size , sizeof(double) };

        // create 2-D NumPy array
        return  py::array(py::buffer_info(
            result.data(),                           /* data as contiguous array  */
            sizeof(double),                          /* size of one scalar        */
            py::format_descriptor<double>::format(), /* data type                 */
            ndim,                                    /* number of dimensions      */
            shape,                                   /* shape of the matrix       */
            strides                                  /* strides for each axis     */
          ));
    }
public:
	ExampleBase()
	{}

	void set_time(double t)
    {
        this->time_ = t;
    }

    double get_time() const
    {
        return this->time_;
    	// set self.t in Python
    }

    void set_result_data(double *data, ssize_t n_rows, ssize_t n_cols, ssize_t size)
    {
        field_result_ = this->create_array_with_data(data, n_rows, n_cols, size);
    }

    void set_result(ssize_t n_rows, ssize_t n_cols, ssize_t size)
    {
        field_result_ = this->create_array(n_rows, n_cols, size);
    }

    void add_to_dict_data(std::string field_name, double *data, ssize_t n_rows, ssize_t n_cols, ssize_t size)
    {
        fields_dict_[field_name.c_str()] = this->create_array_with_data(data, n_rows, n_cols, size);
    }

    void add_to_dict(std::string field_name, ssize_t n_rows, ssize_t n_cols, ssize_t size)
    {
        fields_dict_[field_name.c_str()] = this->create_array(n_rows, n_cols, size);
    }

    void print_fields() const
    {
        std::cout << "Dictionary contains fields: " << std::endl;
        for (auto item : fields_dict_)
        {
        	std::cout << " - " << item.first << ":" << std::endl << item.second << std::endl;
        	// check item.second
        }
    }

protected:
    py::dict fields_dict_;
    py::array field_result_;
    double time_;
};

#endif /* PYTHON_FIELD_BASE_HH_ */
