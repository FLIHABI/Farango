input =b"""
type foo (A) =
{
    a : A;
};

type bar (B, C) =
{
    b : foo(B);
    c : foo(C);
};
"""

rules = [ 'compare_exit_status' ]
