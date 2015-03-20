input = b"""
module test.struct;

type Struct = {
    a : int;
    b : double;
};
""";

rules = ['compare_exit_status']
