Characters
----------

Programs are written using the Unicode 6.2 character set.

Line breaks
~~~~~~~~~~~

A line break is defined as follows:

.. code-block:: ebnf

  line-break = ? ASCII LF character ?
             | ? ASCII CR character ? [? ASCII LF character ?] ;

An input character is defined as any unicode code point that is not a line break.

Whitespaces
~~~~~~~~~~~

A whitespace is defined as follows:

.. code-block:: ebnf

  whitespace = line-break
             | " "                    (* space *)
             | ? ASCII HT character ? (* horizontal tab *) ;

Comments
~~~~~~~~

Comments come in two forms: an inline form, and a block form.

* inline comments (``// text``) mark all the characters from ``//`` until a line breaks
  to be ignored by the compiler.
* block comments (``/* text */``) mark all the characters from ``/*`` until the
  matching ``*/`` to be ignored by the compiler. Block comments may nest.
