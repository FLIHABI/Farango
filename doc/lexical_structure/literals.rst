Literals
--------

A literal is the source code notation for representing the value of a builtin type.

Integer literals
~~~~~~~~~~~~~~~~

An integer literal is the representation of an integer value of base 10 or 16.

.. code-block:: ebnf

  digit = "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9" ;

  hex-digit = digit | "a" | "b" | "c" | "d" | "e" | "f"
                    | "A" | "B" | "C" | "D" | "E" | "F" ;

  integer-literal = decimal-literal
                  | hexadecimal-literal ;

  decimal-literal = {digit} ;

  hexadecimal-literal = "0x" {hex-digit} ;

The largest integer literal is 9223372036854775808 (2^63) -- this number
may only appear as the operand of the unary minus operator (-).
It is a compile time error if 9223372036854775808 (2^63) appear in a context other than
the operand of the unary minus or if the value of an integer literal is greater than
9223372036854775808 (2^63).
It is a compile time error if an hexadecimal integer literal does not fit in 64 bits.

Floating-point literals
~~~~~~~~~~~~~~~~~~~~~~~

A floating-point literal possess a whole-number part, a period, a fraction part, and an exponent:

.. code-block:: ebnf

  number = {digit} ;

  sign = "+" | "-" ;

  exponent = "e" [sign] number ;

  float-num = number "." [number]
            | "." number ;

  float-literal = float-num [exponent] ;

Floating-point literals are converted to the IEEE 754 64-bit double-precision
binary format.

The largest positive finite floating-point literal is 1.7976931348623157e308.
The smallest positive finite non-zero floating-point literal is 4.9e-324.

It is a compile time error if the literal is too large that its IEEE 754
conversion becomes infinity, or if the literal is too small that its IEEE 754
conversion becomes 0.

Boolean literals
~~~~~~~~~~~~~~~~

A boolean literal is either ``true`` or ``false``:

.. code-block:: ebnf

  boolean-literal = "true" | "false" ;

String literals
~~~~~~~~~~~~~~~

A string literal is a sequence of at least one character enclosed by double quotes:

.. code-block:: ebnf

  character = ? all characters except for " and \ ? | escape-sequence ;

  string-literal = '"' {character} '"';

A string literal may contain escape sequences for invisible characters that bear special meaning:

.. code-block:: ebnf

  escape-sequence = "\b" (* backspace *)
                  | "\t" (* horizontal tab *)
                  | "\n" (* line feed *)
                  | "\r" (* carriage return *)
                  | '\"' (* double quote *)
                  | "\'" (* single quote *)
                  | "\\" (* backslash *)
                  ;

It is a compile time error for a line terminator to appear after the opening
double quote and before the closing matching double quote.
