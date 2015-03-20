input = b"""
module test.function;

fun min2(a : int, b : int) = {
    if (a > b) b else a;
};

fun min3(a : int, b : int, c : int) = min2(a, min2(b, c));
"""

rules = [ 'compare_exit_status' ]
