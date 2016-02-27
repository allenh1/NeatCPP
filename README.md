Neat C++
========
 * The purpose of this repository is to demonstrate some of the more bizarre features of C++.
 * This is primarily intended for CS240 students who have nothing better to do (so nobody).
 * Some of this code is pretty terrifying to look at.


List of Examples:
=========
 * FunctionObject
 * LambdaExample
 * TemplateMetaprogramming
 * MaxSubarray

FunctionObject:
---------------
 * This example sorts an array of randomly generated numbers
   by using a function object, or functor.
 * You can compile this example with C++0x through C++17

LambdaExample:
--------------
 * This one is only for the brave. This example is extremely complicated.
 * In this example, we mess around with lambda expressions, creating two
   main expressions: a printer with variable types and arguments, as well
   as a Fibonacci calculator with closure.
 * This example requires C++14 or later, to make use of the auto lambda.

TemplateMetaprogramming:
------------------------
 * This example demonstrates the fascinating notion of template metaprogramming.
 * We use templates and enums to calculate factorials of numbers.
 * This will work with C++0x through C++17

MaxSubarray:
-----------
 * This one is pretty boring. It is just an implementation of the max subarray
   problem. It might need some lambdas to be more fun.

There is also a Qt example for File IO in the QtStuff directory. I will be adding some more of these... In due time.