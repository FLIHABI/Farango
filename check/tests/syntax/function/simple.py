input = b"""
module test.function;

fun test_function(type param0, type param1) = {
    
};

fun const_function() = 42;
"""

rules = [ 'compare_exit_status' ]
