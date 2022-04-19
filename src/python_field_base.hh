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
#include <pybind11/numpy.h>

class PythonFieldBase
{
public:
	PythonFieldBase(std::vector<std::string> field_names)
    : field_names_(field_names) {}

    std::vector<std::string> set_dependency() const
    {
        return this->field_names_;
    }

    const double &set_time(double t)
    {
        this->time_ = t;
        return this->time_;
    	// set self.t in Python
    }

    void cache_reinit()
    {
    	// create Python Numpy wrapped around cache tables, pass shape of the result Value
        // PythonFieldBase keeps:
        //   - table of field names
        //   - table of field shapes
        //   - table of field caches (pointers)
        // Create dictionary self.fields[<field_name>] -> field numpy array of the cache
    }

    void cache_update()
    {
        // call PythonFieldBase::call() implemented in Python.
    }

protected:
    std::vector<std::string> field_names_;
    double time_;
};


#endif /* PYTHON_FIELD_BASE_HH_ */
