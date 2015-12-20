# Makefile
# 
# If you are having trouble building things, verify that your compiler supports c++17.
# Since it probably doesn't, try changing the below to --std=c++14 instead. If you must
# reduce your std library to c++11, then the lambda example should be commented out.
#  auto lambda's require >= c++14. This is being compiled on my machine by GCC >= 5.30
all: FunctionObject MaxSubarray TemplateMetaprogramming LambdaExample

FunctionObject: FunctionObject.cpp
	g++ --std=c++17 -g FunctionObject.cpp -o FunctionObject

MaxSubarray: max-subarray.cpp
	g++ --std=c++17 -g max-subarray.cpp -o MaxSubarray

TemplateMetaprogramming: tmp-fact.cpp
	g++ --std=c++17 -g tmp-fact.cpp -o TemplateMetaprogramming

LambdaExample: lambda.cpp
	g++ --std=c++17 -g lambda.cpp -o LambdaExample
clean:
	rm -f *.o FunctionObject MaxSubarray TemplateMetaprogramming LambdaExample
