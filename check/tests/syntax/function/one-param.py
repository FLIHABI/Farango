input = b"""
module test.function;

fun identity(int e) = e;
"""

rules = [ 'compare_exit_status' ]
