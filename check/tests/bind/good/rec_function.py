input =b"""
fun a() : int;
fun b() : int = a() + 1;
fun a() : int = b() + 1;
"""

rules = [ 'compare_exit_status' ]
