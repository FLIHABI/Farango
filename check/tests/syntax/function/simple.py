input = b"""
module test.function;

fun test_function(int param0, int param1) = {
    
};

fun const_function() = 42;
"""

rules = [ 'compare_exit_status' ]
