Types
=====

.. code-block:: ebnf

  type = primitive-type | structure-type | union-type | empty-type ;

  type-prefix = "type" identifier [generic-list] ;

  generic-list-r = identifier | identifier "," generic-list-r ;
  generic-list = "(" generic-list-r ")" ;

Empty types
-----------

An empty type is an abstraction on the concept of "nothing". A variable with
an empty type always hold a value representing "nothing".

Value of empty types are not compatible between each other.

.. code-block:: ebnf

  empty-type = type-prefix ;

Primitive types
---------------

The following types are known as primitive types:

* int (64-bit integer)
* float (64-bit double precision floating point number)
* bool

.. code-block:: ebnf

  primitive-type = "int" | "float" | "bool" ;

Structure types
---------------

Structure types are records that contain one or more fields. Each field is denoted
by an identifier that is unique to the record, and a type.

.. code-block:: ebnf

  structure-type = type-prefix "=" "{" field-list "}" ;

  field-list = field
             | field ";" field-list ;

  field = identifier ":" type-identifier ;

Union Types
-----------

Union types denote an abstract type representing the logical union of all the
specified types -- a value with a type that is contained within an union can fit
in a variable of this union type.

.. code-block:: ebnf

  union-type = type-prefix "=" type-list ;

  type-list = type-identifier
            | type-identifier "|" type-list ;

