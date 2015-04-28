input = b"""
module test.maybe;

type Nothing = {};
type Just A = {
    value : A;
};

type Maybe A = Just A | Nothing;
""";

rules = ['compare_exit_status']
