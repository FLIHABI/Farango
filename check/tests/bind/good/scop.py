input =b"""
var a : int = 42;
{
    var a : int = 21;
};
"""

rules = [ 'compare_exit_status' ]
