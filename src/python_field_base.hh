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

namespace py = pybind11;


/// Helper class, holds data of one field
class FieldCacheProxy
{
public:
    /// Constructor
	FieldCacheProxy(std::string field_name, std::vector<size_t> shape, std::vector<double> field_cache_ptr)
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
	const std::vector<size_t> &shape() const { return shape_; }
	std::vector<double> &field_cache_ptr() { return field_cache_ptr_; }
private:
    std::string field_name_;
    std::vector<size_t> shape_;
    std::vector<double> field_cache_ptr_;
};


class PythonFieldBase
{
public:
    PythonFieldBase(std::vector<FieldCacheProxy> data)
    : fields_data_(data) {}

    py::list set_dependency() const
    {
        std::vector<std::string> field_names(fields_data_.size());
        for (uint i=0; i<fields_data_.size(); ++i) {
            field_names[i] = fields_data_[i].field_name();
        }
        py::list field_list = py::cast(field_names);
        return field_list;
    }

    void set_time(double t)
    {
        this->time_ = t;
    }

    double get_set_time() const
    {
        return this->time_;
    	// set self.t in Python
    }

    py::dict cache_reinit()
    {
        // Create dictionary self.fields[<field_name>] -> field numpy array of the cache
        py::dict d;
    	for (uint i=0; i<fields_data_.size(); ++i) {
    	    std::vector<size_t> strides = { (fields_data_[i].shape()[1]*sizeof(double)) };
    		py::array data(fields_data_[i].shape(), strides, fields_data_[i].field_cache_ptr() ); // numpy array
            d[fields_data_[i].field_name()] = data;
        }
    	return d;
    }

    void cache_update()
    {
        // call PythonFieldBase::call() implemented in Python.
    }

protected:
    std::vector<FieldCacheProxy> fields_data_;
    double time_;
};


#endif /* PYTHON_FIELD_BASE_HH_ */
