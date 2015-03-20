input = b"""
module test.function;

fun test_function(param0 : int, param1 : int) = {};

fun const_function() = 42;
"""

rules = [ 'compare_exit_status' ]
