Tokens
------

Tokens are the terminal symbols of the syntactic grammar, that are neither
whitespace nor comments.

A token is either an identifier, a keyword, a literal, or a symbol:

.. code-block:: ebnf

  token = identifier | keyword | literal | symbol ;
