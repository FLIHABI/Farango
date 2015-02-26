Expressions
===========

Everything in Farango has a value -- there are no statements, only
expressions.

Binary Operators
----------------

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

========== ===========
Operator   Description
========== ===========
``!``      Logical not
``~``      Bitwise not
``-``      Minus
``+``      Plus
``++expr`` Pre-increment
``--expr`` Pre-decrement
``expr++`` Post-increment
``expr--`` Post-decrement
========== ===========

Operator precedence
-------------------

==================== ====================================
Operator             Precedence
==================== ====================================
Postfix              ``expr++`` ``expr--``
Unary                ``++expr`` ``--expr`` ``+expr`` ``-expr`` ``~`` ``!``
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

    (<>) = (!=)
