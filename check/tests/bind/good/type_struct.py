input =b"""
type B;
type A = { b : B; };
type B = { a : A; };
"""

rules = [ 'compare_exit_status' ]
