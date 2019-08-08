#include <iostream>
#include <vector>
#include <functional>

template <typename T, typename Func>
void ForEach(std::vector<T>& container, Func const& lambdaExpression)
{
	for (auto& el : container) {
		el = lambdaExpression(el);	
	}
}

void ForEachAuto(std::vector<auto>& container, auto const& lambdaExpression)
{
	for (auto& el : container) {
		el = lambdaExpression(el);	
	}
}

// Compiles without cast at calling site - but not very flexible/useful.
// No point having the container templated if the function is rigidly
// coupled to a specific type.
template <typename T>
void ForEach2(std::vector<T>& container, std::function<int(const int &)> f)
{
	for (auto& el : container) {
		el = f(el);	
	}
}

template <typename T>
void printVec(std::vector<T> v)
{
	for (const auto& el : v)
		std::cout << el << " ";
	std::cout << '\n';
}

int main()
{
	std::vector<int> intVec = { 0,1,2,3,4,5 };
	printVec(intVec);

	ForEachAuto(intVec, [](auto x){ return x * x; });
	printVec(intVec);

	// Full syntax
	int a = 10;
	ForEach(intVec, [&a] (int x) -> int{ return a * x;});
	printVec(intVec);

	std::vector<double> doublesVec = { 1.1,2.2,3.3,4.4,5.5 };
	ForEach(doublesVec, [](auto x){ return x * x; });
	printVec(doublesVec);

	std::vector<std::string> stringVec = { "Pallas", "Ceres", "Vesta" };
	// Lambda to uppercase each string in the vector
	ForEach(stringVec, [](auto s) { for (auto it = s.begin(); it != s.end(); ++it) {*it = toupper(*it);} return s; });
	printVec(stringVec);

	return 0;
}
