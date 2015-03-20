input = b"""
module test.function;

fun identity(e : int) = e;
"""

rules = [ 'compare_exit_status' ]
