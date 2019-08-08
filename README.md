Lambdas in C++
==============

In C++ a _lambda expression_ or _lambda function_ is a [closure][1]: an unnamed (anonymous) function that is passed inline - usually to another function. Lambda expressions are a concise way of creating simple function objects.

If necessary, lambda expressions can capture variables from their context.

Lambda expressions are useful for passing an operation as an argument into an algorithm.

Using a lambda expression is like using a function pointer, but without the need to create a named object.

Syntax
------
Full syntax:

```c++
// [captures] (params) -> returnType { function body }

// Concrete example: capture a by reference; parameter is int; lambda expression returns an int 
int a = 10;
ForEach(intVec, [&a] (int x) -> int{ return a * x; });
```

If the return type can be deduced from the return statement in the function body, the return type can be ommitted:

```c++
// [captures] (params) { function body }
// Concrete example: No captures, parameter is int, lambda expression returns an int
ForEach(intVec, [] (int x) { return x * x; });
```
If the lambda expression takes no arguments:

```c++
// [captures] { function body }
// Concrete example: no captures, no parameters:
ForEach(intVec, []{ return 0; }
```

For other syntax options: [https://en.cppreference.com/w/cpp/language/lambda][2]

Generic Lambda Expression
-------------------------
Lambda expressions can take arguments that have arbitrary types.

If a parameter is marked `auto`, the type can be deduced:

```c++
ForEach(intsVec, [] (auto x) { return x * x });
```
In this case, the lambda expression becomes an instance of type:

```c++
class // unnamed
{
public:
	template<typename T>
	T operator() (T x) const { return x * x }
};

```

If a generic lambda has no captures, the closure type has a "public non-virtual non-explicit const conversion function template to pointer to function" [see the standards document][4].

Passing Generic Lambda to Template Function
-------------------------------------------
In the following example, `ForEach()` can transform elements of a vector - the type of the element being generic.

The generic lambda is straightforward enough, but note the template function signature - the 

```c++
#include <iostream>
#include <vector>

template <typename T, typename Func>
void ForEach(std::vector<T>& container, Func f)
{
	for (auto& el : container) {
		el = f(el);	
	}
}

// Equivalent:
void ForEachAuto(std::vector<auto>& container, auto const& lambdaExpression)
{
	for (auto& el : container) {
		el = lambdaExpression(el);	
	}
}

int main()
{
	std::vector<int> intVec = { 0,1,2,3,4,5 };
	ForEach(intVec, [](auto x){ return x * x; });
	// intVec is now { 0,1,4,9,16,25 }	

	std::vector<double> doublesVec = { 1.1,2.2,3.3 };
	ForEach(doublesVec, [](auto x){ return x * x; });
	// doublesVec is now { 1.21, 4.84, 10.89 }

	return 0;
}
```

In the code above, the argument for f can be a:

- Lambda expression
- `std::function`
- functor
- function pointer

Note that you can't pass a lambda function object as an argument of type `std::function<T>` without explicitly specifying T.

This is because template type deduction tries to match type of the lambda with the type of `std::function<T>` which is not possible because types are different.

References
----------
* [C++ Standards Committee ISOCPP][4]: Lambda expressions
* [Closures][1]
* [Syntax][2]
* [Generic Lambdas][3]

[1]: https://en.wikipedia.org/wiki/Closure_(computer_programming)
[2]: https://en.cppreference.com/w/cpp/language/lambda
[3]: https://stackoverflow.com/a/17233649/3590673
[4]: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3690.pdf#subsection.5.1.2
