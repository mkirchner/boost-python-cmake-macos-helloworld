/*
 * chello_ext.cpp
 */

#include <boost/python.hpp>
#include "chello.h"

BOOST_PYTHON_MODULE(chello_ext) {
    using namespace boost::python;
    def("greet", greet);
}

