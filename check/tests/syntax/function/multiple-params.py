input = b"""
module test.function;

fun min2(a, b) = {
    if (a > b) b else a;
};

fun min3(a, b, c) = min2(a, min2(b, c));
"""

rules = [ 'compare_exit_status' ]
