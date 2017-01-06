/*
 * chello_ext.cpp
 * Copyright (C) 2017 Marc Kirchner
 *
 * Distributed under terms of the MIT license.
 */

#include <boost/python.hpp>
#include "chello.h"

BOOST_PYTHON_MODULE(chello_ext) {
    using namespace boost::python;
    def("greet", greet);
}

