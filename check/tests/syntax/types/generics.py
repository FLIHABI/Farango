input = b"""
module test.generics;

type Generic(A) = { a : A; };
"""

rules = ['compare_exit_status']
