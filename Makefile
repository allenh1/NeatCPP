all: FunctionObject MaxSubarray TemplateMetaprogramming

FunctionObject: FunctionObject.cpp
	g++ --std=c++14 -g FunctionObject.cpp -o FunctionObject

MaxSubarray: max-subarray.cpp
	g++ --std=c++14 -g max-subarray.cpp -o MaxSubarray

TemplateMetaprogramming: tmp-fact.cpp
	g++ -std=c++14 -g tmp-fact.cpp -o TemplateMetaprogramming
clean:
	rm -f *.o FunctionObject MaxSubarray TemplateMetaprogramming
