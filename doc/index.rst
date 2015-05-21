Farango
=======

**DISCLAIMER:** This document is a work in progress. It's content may change
at any given moment and should not be built upon.

Language goals
--------------

* Be distributed out of the box. Concurrency and distribution should be
  easy to do.

    * As a result, the language would benefit from immutable data
      structures
    * Functional languages are best fit candidates for these kind of
      tasks

* Be fast. If the benefits of distributed calculations are outdone
  by poor optimisation, this would be useless.
* Be safe and high-level. The programmer should work on a *theoric machine*,
  and as such, the language should abstract away the inner work.

 .. toctree::
    :maxdepth: 3

    lexical_structure/index
    expressions
    callables
