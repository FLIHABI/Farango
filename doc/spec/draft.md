# Farango specification draft

**DISCLAIMER:** This document is a work in progress. It's content may change
at any given moment and should not be built upon.

## Language goals:

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

## Core

### Modules

TODO

```
module module_name
import some_module
import some.nested.module
import .sibling_module
import ..relative_to_parent_module
```

### Variables and expressions

#### Operators

##### Arithmetic

##### Applicative

##### Ternary

##### Slices

### Statements

#### Conditionals

#### For loops

#### Foreach loops

#### While loops

#### Control flow

* `break [label]` (for, foreach, while) halts the current execution and resume after
  the control block optionally specified by `label`.
* `continue [label]` (for, foreach, while) halts the current iteration and resume at the start of
  the control block optionally specified by `label`.

### Callables (Functions, Coroutines, Tasks)

#### Syntax

```
fun function_name(parameters) {
  body
}
```

#### Control flow

In addition to the standard control flow statements, the following
statements are provided to change the control flow in any callable:

* `return <expr>`: returns the value of the given expression in a function.
  Execution of the current function stops.
* `yield <expr>`: yields the value of the given expression in a coroutine.
  Execution resumes after this point when the coroutine is called again.
* `offer <expr>`: offers the value of the given expression in a task to the
  underlying task manager. Execution of the current function stops.

### Types

#### Scalar types

Scalar types are types that does not have any other components.

The language should provide the following native types:

* `bool` shall be a type accepting two kinds of value: `true` or `false`.
* `byte` shall be the smallest addressable unit of the running machine,
  and is an integer type.
* `short` and `ushort` shall respectively be signed and unsigned integer
  types with size of 2 `byte`s.
* `int` and `uint` shall respectively be signed and unsigned integer types
  with size of 4 `byte`s.
* `long` and `ulong` shall respectively be signed and unsigned integer types
  with size of 8 `byte`s.

#### Array types

Array types shall represent a collection of sequential elements with
random access, with each element being of only one component type.

Array types shall be declared by appending `[]` after the component type.

component types may be any type, even array types.

#### Complex types

Complex types shall represent a finite set of elements of different
component types.

It shall be declared with the following syntax:

```
type type_name {
  component_type_1 field_name_1;
  component_type_2 field_name_2;
  ...
}
```

### Qualifiers

The language shall provide qualifiers to help the compiler optimize
some functions.

#### Type qualifiers

* `immutable`: the type is immutable. Variables using this type shall not
  and cannot be modified through any means after they have been
  initialized.

#### Function qualifiers

* `pure`: the function has no side effects. Its result is guaranteed
  to not change given the same parameters.
