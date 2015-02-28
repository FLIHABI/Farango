input = b"""
module test.control;

do {} while (true);
"""

rules = [ 'compare_exit_status' ]
