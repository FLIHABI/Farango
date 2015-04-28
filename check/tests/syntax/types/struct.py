input = b"""
module test.struct;

type Struct = {
    a : int;
    b : string;
};
""";

rules = ['compare_exit_status']
