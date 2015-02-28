input = b"""
module test

import .relative
"""

rules = [ 'compare_exit_status' ]
