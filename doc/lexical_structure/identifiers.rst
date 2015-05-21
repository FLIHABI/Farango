Identifiers
-----------

An indentifier is an unbounded sequence of word characters, the first of which
must not be a digit.

.. code-block:: ebnf

  identifier-start = ? any non-digit letter ([:alpha:]) ? ;
  identifier-part = ? any alphanumeric character ([:alnum:]) ? ;

  identifier = ? (identifier-start [{identifier-part}]) but not a keyword or a boolean-literal ?

It is a compile time error for an identifier to have the same spelling than
a keyword or a boolean literal.

Two identifiers are the same if they contain the same contents; i.e. each of
their characters are two-by-two equal.
