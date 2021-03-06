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

// Hides warning: "PythonFieldBase" declared with greater visibility than the type of its field ...
// #pragma GCC visibility push(hidden)

/// Helper class, holds data of one field
class FieldCacheProxy
{
public:
    /// Constructor
	FieldCacheProxy(std::string field_name, std::vector<ssize_t> shape, std::vector<double> field_cache_ptr)
    : field_name_(field_name), shape_(shape), field_cache_ptr_(field_cache_ptr)
    {
	    shape_.resize(2); // shape_[1] < number of components
	                      // shape_[0] < size of one component
	    if (shape.size()==1) shape_[1] = shape[0];
	    else if (shape.size()==2) shape_[1] = shape[0] * shape[1];
	    //else "error"
	    shape_[0] = field_cache_ptr_.size() / shape_[1];
    }

    /// Getters
	const std::string &field_name() const { return field_name_; }
	const std::vector<ssize_t> &shape() const { return shape_; }
	std::vector<double> &field_cache_ptr() { return field_cache_ptr_; }
private:
    std::string field_name_;
    std::vector<ssize_t> shape_;
    std::vector<double> field_cache_ptr_;
};


class PythonFieldBase
{
public:
    PythonFieldBase(std::vector<FieldCacheProxy> &data, FieldCacheProxy &result)
    {
    	py::dtype d_type("float64");

    	// Fill dictionary of input fields
    	for (uint i=0; i<data.size(); ++i) {
    		py::detail::any_container<ssize_t> shapes( data[i].shape() );
    		py::detail::any_container<ssize_t> strides = { (data[i].shape()[1]*sizeof(double)) };
    		py::array field_data(d_type, shapes, strides, &(data[i].field_cache_ptr()[0]) ); // numpy array
    		fields_dict_[data[i].field_name().c_str()] = field_data;
        }
    	// Fill array of result field
    	{
    		py::detail::any_container<ssize_t> shapes( result.shape() );
    		py::detail::any_container<ssize_t> strides = { (result.shape()[1]*sizeof(double)) };
    		field_result_ = py::array(d_type, shapes, strides, &(result.field_cache_ptr()[0]) );
    	}
    }

//    py::list get_dependency() const
//    {
//        std::vector<std::string> field_names;
//        for (auto item : fields_dict_)
//        {
//        	field_names.push_back(item.first);
//        }
//        py::list field_list = py::cast(field_names);
//        return field_list;
//    }

    void set_time(double t)
    {
        this->time_ = t;
    }

    double get_time() const
    {
        return this->time_;
    	// set self.t in Python
    }

    py::dict cache_reinit()
    {
        // Create dictionary self.fields[<field_name>] -> field numpy array of the cache
    	return fields_dict_;
    }

    void cache_update()
    {
        // call PythonFieldBase::call() implemented in Python.
    }

protected:
    py::dict fields_dict_;
    py::array field_result_;
    double time_;
};


#endif /* PYTHON_FIELD_BASE_HH_ */
