input =b"""
var i : int = 42;
while (i > 0)
{
    i = i / 2;
    var i : int = i;
};

while ( { var i : int = i; i != 0; } )
{
    i = i / 2;
};

do
{
    var i : int = i;
} while (i);
"""

rules = [ 'compare_exit_status' ]
