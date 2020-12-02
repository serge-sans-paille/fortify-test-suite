Test suite for __builtin_*_chk
==============================

A collection of tests for compiler who wants to support glibc's fortify feature,
the one triggered by `-D_FORTIFY_SOURCE=1` or `-D_FORTIFY_SOURCE=2`.

This tests compile time and runtime behavior of a few functions that involve
call to compiler builtins like `__builtin_memcpy_chk`.

To run the whole suite:

.. code-block:: sh

    # run the tests with gcc, should pass with a relatively modern gcc version
    make check-gcc

    # run the tests with clang, runtime checks don't pass, but compile-time
    # checks are generally ok
    make check-clang

    # run all tests
    make check

    # run only dynamic checks
    make check STATIC_CHECK=false

    # run tests for specific functions, e.g. memcpy
    make test-memcpy

To test another compiler, add its name in the `COMPILERS` variable in the
Makefile and ensure that it is in `PATH`; then for a compiler `CC`, its tests
can be invoked using `make check-CC`.
