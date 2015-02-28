input = b"""
module test.control;

if (true) {} else {};
"""

rules = [ 'compare_exit_status' ]
