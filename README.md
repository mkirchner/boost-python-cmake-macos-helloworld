A minimal CMake boost::python example for MacOS
===============================================

For some reason this has been hard to find on the internet.


Prerequisites
-------------

Make sure you have `homebrew` installed, then:

        brew install boost-python

For Python3:

        brew install boost-python --with-python3

In any case, make sure that you have matching calls to
`find_package` for `PythonLibs` and `Boost` in your `CMakeLists.txt`.


For Python 3:

        find_package(PythonLibs 3.5 REQUIRED)
        ...
        find_package(Boost COMPONENTS python3 REQUIRED)
        ...

For Python 2:

        find_package(PythonLibs 2.7 REQUIRED)
        ...
        find_package(Boost COMPONENTS python REQUIRED)
        ...


Learnings
---------

* The name of the module in the `BOOST_PYTHON_MODULE(name)` declaration
  must *exactly* match the name of the shared library. Hence, we need
  to explicitly disallow the standard `lib...` prefix that CMake uses
  for shared libs:

        set_target_properties(chello_ext PROPERTIES PREFIX "")


* Python will only search for shared libraries that have a `.so` 
  extension. Consequently, we explicitly need to define the appropriate
  suffix to avoid the macOS `.dylib` standard:

        set_target_properties(chello_ext PROPERTIES SUFFIX ".so")

* Most of the examples on the internet lack the reference to the Python
  libraries in the link command.

        target_link_libraries(chello_ext ${Boost_LIBRARIES} ${PYTHON_LIBRARIES}
        chello)
