input = b"""
module test.control;

if (1) {} else {};
"""

rules = [ 'compare_exit_status' ]
