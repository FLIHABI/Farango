input = b"""
module test.control;

do {} while (1);
"""

rules = [ 'compare_exit_status' ]
