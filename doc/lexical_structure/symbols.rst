Symbols
-------

Symbols in the grammatical context of Farango are either separators or operators:

.. code-block:: ebnf

  symbol = separator | operator ;

Separators
~~~~~~~~~~

The following tokens are used as separators:

.. code-block:: ebnf

  separator = "(" | ")" | "{" | "}" | "[" | "]" | ";" | "," | "." ;

Operators
~~~~~~~~~

An operator is a sequence of one or more operator characters:

.. code-block:: ebnf

  operator-char = "!" | "#" | "$" | "%" | "&" | "*" | "+" | "-" | "/"
                | ":" | "<" | "=" | ">" | "?" | "@" | "^" | "|" | "~" ;

  operator = {operator-char}
