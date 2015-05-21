Expressions
===========

Everything in Farango has a value -- there are no statements, only
expressions.

Binary Operators
----------------

Binary operators are operators taking two parameters. Invoking an operator
can be done with two possible syntaxes:

* Operator-like: ``<expr> <op> <expr>``
* Function-like: ``(<op>)(<expr>, <expr>)``

The language shall natively provide the following operators:

======== ===========
Operator Description
======== ===========
``*``    Multiplication
``/``    Division
``%``    Modulo
``+``    Addition / Union
``-``    Subtraction
``==``   Equal
``!=``   Not equal
``>``    Greater than
``<``    Less than
``>=``   Equal or greater than
``<=``   Equal or less than
``<=>``  Compare
``&&``   Logical AND
``||``   Logical OR
``>>``   Bitwise right shift
``<<``   Bitwise left shift
``^``    Bitwise XOR
``|``    Bitwise OR
``&``    Bitwise AND
======== ===========

Unary operators
---------------

Unary operators, unlike binary operators, only take one parameter.

The language shall natively provide the following operators:

========== ===========
Operator   Description
========== ===========
``!``      Logical not
``~``      Bitwise not
``-``      Minus
``+``      Plus
========== ===========

Operator precedence
-------------------

Operators in an expression have evaluation priority: this is called
precedence. An operator takes precedence over an other operator if it
is evaluated before the other. As an example, ``*`` takes precedence over
``+``, because ``a + b * c`` can be expanded to ``a + (b * c)``, and not
``(a + b) * c``.

Below is a table of operators sorted from high precedence (top) to low
precedence (bottom):

==================== ====================================
Operator             Precedence
==================== ====================================
Unary                ``+expr`` ``-expr`` ``~`` ``!``
User-defined
Multiplicative       ``*`` ``/`` ``%``
Additive             ``+`` ``-``
Shift                ``<<`` ``>>``
Relational           ``<`` ``>`` ``<=`` ``>=`` ``<=>``
Equality             ``==`` ``!=``
Bitwise AND          ``&``
Bitwise XOR          ``^``
Bitwise OR           ``|``
Logical AND          ``&&``
Logical OR           ``||``
Assignment           ``=`` ``+=`` ``-=`` ``*=`` ``/=`` ``%=`` ``&=`` ``^=`` ``|=`` ``<<=`` ``>>=``
==================== ====================================

User defined operators
----------------------

User may define or overload operators by declaring a function with the
operator symbol enclosed in parenthesis as identifier:

.. code-block:: farango

    fun (<>)(lhs, rhs) = {
        lhs != rhs
    }

Here we declare the binary operator ``<>`` as an alias of ``!=``.
Alternatively, one could implement the operator as:

.. code-block:: farango

    var (<>) = (!=)

There are no requirements on the purity of user-defined operators, but
programmers should aspire to make their operators pure.

There are also no requirements on operators laws, with some exceptions on
default operator overloads:

* ``+``, ``*``, ``^``, ``|``, ``&``, ``==`` and ``!=`` shall be
  associative and commutative.
* All comparison operators shall be transitive.
