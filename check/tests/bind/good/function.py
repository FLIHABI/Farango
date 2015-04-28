input = b"""

fun toto(); /* Proto */
toto();     /* call */
fun toto() = if (0) toto(); /* declaration, recursivity*/
toto(); /* second call */
"""

rules = [ 'compare_exit_status' ]
