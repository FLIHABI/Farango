input =b"""
var i : int;
for (i = 0; i < 21; i = i + 1)
{
    var i : int = i;
};

for (var y : int = 0; y < 21; y = y + 1)
{
    var y : int = y;
};
"""

rules = [ 'compare_exit_status' ]
