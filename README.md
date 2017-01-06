A minimal CMake boost::python example for MacOS
===============================================

A minimal `boost::python` "Hello World!" example in the form of a `chello_ext`
Python module.

For some reason it has been hard to find something on the internet that
actually compiles, links and is loadable as a Python module on macOS.


macOS prerequisites
-------------------

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


Testing it out
--------------

```
$ git clone git@github.com:mkirchner/boost-python-cmake-macos-helloworld.git
Cloning into 'boost-python-cmake-macos-helloworld'...
...
Receiving objects: 100% (3/3), done.

$ cd boost-python-cmake-macos-helloworld

$ mkdir build

$ cd build

$ cmake ..
-- The C compiler identification is AppleClang 8.0.0.8000038
-- The CXX compiler identification is AppleClang 8.0.0.8000038
...
-- Configuring done
-- Generating done
-- Build files have been written to: /your/path/boost-python-cmake-macos-helloworld/build

$ make
Scanning dependencies of target chello
[ 25%] Building CXX object CMakeFiles/chello.dir/chello.cpp.o
[ 50%] Linking CXX shared library libchello.dylib
[ 50%] Built target chello
Scanning dependencies of target chello_ext
[ 75%] Building CXX object CMakeFiles/chello_ext.dir/chello_ext.cpp.o
[100%] Linking CXX shared library chello_ext.so
[100%] Built target chello_ext

$ python3
Python 3.5.2 (default, Sep 28 2016, 18:08:09) 
[GCC 4.2.1 Compatible Apple LLVM 8.0.0 (clang-800.0.38)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> import chello_ext
>>> print(chello_ext.greet())
Hello, world!
>>> 
```

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
