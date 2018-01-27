Shorthand syntax for creation and usage of ranges
=================================================

This document tries to define a reasonable and meaningful definition of a more concise syntax for
creating and using ranges in C++.
Using ranges of iterable containers is currently quite cumbersome. Eric Niebler's range library
improves on a lot of the present problems, but a more concise way of writing mathematical and
numerical code would be a great improvement. Especially with respect to slicing of multidimensional
data arrays, a more pythonic syntax of ranges would make code shorter and easier to read.

As references, see for example
- http://ericniebler.com/2014/12/07/a-slice-of-python-in-c/
- http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/n4671.pdf
- https://www.reddit.com/r/cpp/comments/6ngkgc/2017_toronto_iso_c_committee_discussion_thread/


Python
-------------------------------------------------

In Python, ranges are either explicitly created, e.g. `for i in range(10)`, or given with the `:` syntax in
the default array/list/whatever `operator[]`, e.g. `x = y[:10]`. `for i in :10` is illegal.


Definitions
-------------------------------------------------

- any `type..type` is interpreted as a range construction, where the operands may determine the type of range
- a `range..difference_t` statement is interpreted as a range construction with a stride
- therefore a `3..12..2` is a `range<int>(3,12,2)`, i.e. a range from 3 to (including) 11 with stride 2
- therefore a `'a'..'g'` is a `range<char>('a', 'g')`

This would allow free-standing range declarations and lots of potential use-cases.


Language changes
-------------------------------------------------

TODO...


Standard library changes
-------------------------------------------------

TODO...


Usage examples
-------------------------------------------------

Basic integer ranges:
```C++
// Without stride
range r = 5..10;     // range [5..10]  stride 1
range r = ..10;      // range [0..10]  stride 1
range r = 5..;       // range [5..end] stride 1
range r = ..;        // range [0..end] stride 1
// With stride
range r = 5..10..2;   // range [5..10]  stride 2
range r = ..10:2;    // range [0..10]  stride 2
range r = 5....2;     // range [5..end] stride 2 <----- this one is not nice to read!
range r = ....2;      // range [0..end] stride 2 <----- this one is not nice to read!
```

Range-based for loop:
```C++
// Loop over index range
for (int i : 5..10) // same as: for (int i : range(5,10))
{
  vec[i] ...;
}
// Loop over array slice
for (double& val : vec[5..10]) // same as: for (double& val :  vec[range(5,10)])
{
  sum += val;
}
// Loop over enumerate of array slice
for ([int i, double& val] : enumerate(vec[5..10])) // quite close to python: for i, val in enumerate(vec[5:10])
{
  vec2[i] += val;
}
```

Should overloads be defined on top of basic and std types?
```C++
int * c_arr;             // a simple pointer, i.e. we don't know the array's size
std::array<int, 10> arr; // std::array, i.e. we know the size

std::array<int, 5> a1 = c_arr[..];   // illegal, as `end` is unknown
std::array<int, 5> a2 = c_arr[3..8]; // legal, as `range` has the correct compile-time size. However, this may cause a runtime exception running out of bounds
std::array<int, 5> a3 = arr[3..8];   // legal, as `range` has the correct compile-time size. Cannot fail at runtime, as the bounds are checked at compile-time
```


User implementations
-------------------------------------------------

By implementing a `Cursor`, which is used by a `Range Facade`, a user can define his own
range behaviour simply by implementing `current`, `next` and `done`. If a strided range is
needed, probably `distance_to` and `advance` are needed, too.



Problems
-------------------------------------------------

- Unconstrained ranges are syntactically ugly, e.g. `....5` for an infinite range of stride 5


Open Questions
-------------------------------------------------

- which types should the `..` syntax support? My use cases are only integer...
- could we emulate this with string literals, e.g. `"3..5"r`?
- what features of range-v3 should be used?
- what exactly needs to change in the language itself and what in the stdlib?

