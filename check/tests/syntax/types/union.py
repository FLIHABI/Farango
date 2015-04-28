input = b"""
module test.union;

type A = {};
type B = {};

type Union = A | B;
""";

rules = ['compare_exit_status']
