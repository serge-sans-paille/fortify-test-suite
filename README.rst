Test suite for __builtin_*_chk
==============================

A collection of tests for compiler who wants to support glibc's fortify feature,
the one triggered by ``-D_FORTIFY_SOURCE=1``.

This tests compile time and runtime behavior of a few functions that involve
call to compiler builtins like ``__builtin_memcpy_chk``.

To run the whole suite:

.. code-block:: sh

    # run the tests with gcc, should pass with a relatively modern gcc version
    make check-gcc

    # run the tests with clang, runtime checks don't pass, but compile-time
    # checks are generally ok
    make check-gcc

    # run all tests
    make check

The makefile is relatively generic, if one wants to test another compiler...
