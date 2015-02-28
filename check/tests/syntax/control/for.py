input = b"""
module test.control;

for (i = 0; i < 42; i = i + 1) {};
"""

rules = [ 'compare_exit_status' ]
