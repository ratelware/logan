*** This document was created as an example of using Markdown for documenting stuff ***

Basically what will be written here is a list of common structures, operators and relation often used in programming practice, listed with their main properties. 

This is basically inspired by math, functional programming and Haskell rules, but it can be as well used in C++ code. It might not be provable so easily, but the ideas are fundamentally same.

One of the problems in programming is that there is currently no way to enforce these rules and make programmers really obey them. So basically - if you do, it is cool, but if you do not, the compiler will not blame you. Other programmers will, of course, but then you may be already far far away.

**Operators**

*Equality and inequality*
In C++ `==` and `!=`, should obey the following laws:
  - a == b -> b == a (commutative)
  - a == b && b == c -> a == c (transitive)
  - a != b && b == c -> a != c (transitive)

* Greater than and less than*
In C++ `<` and `>` should obey the following laws:
  - a > b && b > c -> a > c (transitive)
  - a < b && b < c -> a < c (transitive)

* Greater or equal and less or equal then*
In C++ `=<` and `=>` should obey the following laws:
  - a =< b -> a == b || a < b
  - a => b -> a == b || a > b

**Structures**

*Stack*
  - pop(push(s,d)) = d, s



**Relations**


