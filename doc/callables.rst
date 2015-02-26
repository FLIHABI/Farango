Callables
=========

A callable is an object that, given a set of inputs known as *parameters*
produce one output known as the *return value* through a sequence of
computations.

Declaration
-----------

A callable can be declared with the following syntax:

.. code-block:: farango

    fun <identifier>(<param0>, <param1>, [...], <paramN>) = <expression>

where ``<identifier>`` is the name which the callable shall be refered to
in the module, ``<param0>`` through ``<paramN>`` are the identifiers of each
parameter, and ``<expression>`` is the expression that shall be evaluated
when the callable is invoked.

Invokation
----------

Callable invokation is done by specifying its identifier, then the list of
its parameters enclosed in parenthesis:

.. code-block:: farango

    <identifier>(<param0>, <param1>, [...], <paramN>)

Purity
------

A callable is called *pure* when it has no side-effects, and when given a set
of parameters, two invokations does produce the same return value.

A common example of pure callables are the arithmetic operators.

Functions
---------

Functions are the default (and most used) kind of callables. It has an
internal context that is the parameters and local variables, and is
destroyed when a return value is produced.

Coroutines
----------

Coroutines are the second kind of callables, and can be inferred from the
usage of the ``yield`` control flow keyword. They are much like functions,
except that the internal context of the function is not discarded when a return
value is produced. Instead, the context is saved, and the coroutine shall
resume when it is invoked again later.

Tasks
-----

Tasks are the final kind of callables, and they express a way to make
asynchronous tasks units that can be passed on different execution
environments. Tasks can be inferred from the usage of the ``offer``
control flow keyword, and much like functions, their execution context is
destroyed after a return value has been offered.

Control Flow
------------

In addition to the standard control flow statements, the following
statements are provided to change the control flow in any callable:

* ``return <expr>``: returns the value of the given expression in a function.
  Execution of the current function stops.
* ``yield <expr>``: yields the value of the given expression in a coroutine.
  Execution resumes after this point when the coroutine is called again.
* ``offer <expr>``: offers the value of the given expression in a task to the
  underlying task manager. Execution of the current function stops.
