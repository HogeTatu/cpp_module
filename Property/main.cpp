/**
 *	The MIT License (MIT)
 *
 *	Copyright (c) 2013 HogeTatu
 *
 *	Permission is hereby granted, free of charge, to any person obtaining a copy of
 *	this software and associated documentation files (the "Software"), to deal in
 *	the Software without restriction, including without limitation the rights to
 *	use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 *	the Software, and to permit persons to whom the Software is furnished to do so,
 *	subject to the following conditions:
 *
 *	The above copyright notice and this permission notice shall be included in all
 *	copies or substantial portions of the Software.
 *
 *	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 *	FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 *	COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 *	IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 *	CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <iostream>
#include <string>
#include "Property.h"

template <typename T>
struct OutputLogSetter
{
	static void Set(T* pValue, const T& value)
	{
		*pValue = T(value);
		std::cout << "set:" << value << std::endl;
	}
};

class Sample
{
public:
	Sample()
		: foo1(1)
		, bar1("bar1")
		, foo2(2)
		, bar2("bar2")
	{}
	
	cpp_module::WritableProperty<int>			foo1;
	cpp_module::WritableProperty<std::string>	bar1;
	cpp_module::ReadOnlyProperty<int>			foo2;
	cpp_module::ReadOnlyProperty<std::string>	bar2;

	void setFoo1(int var)
	{
		foo1 = var;
	}

	void setFoo2(int var)
	{
		//foo2 = var;
	}
};

void output(int var)
{
	std::cout << var << std::endl;
}

void output(const std::string& var)
{
	std::cout << var.c_str() << std::endl;
}

int main(int argc, char const *argv[])
{
	std::string str("hoge");
	str = "hoge1";

	Sample sample;
	sample.foo1 = 10;
	sample.bar1 = "sample.bar1";
	output(sample.foo1);
	output(sample.bar1);

	//sample.foo2 = 20;					// error!!
	//sample.bar2 = "sample.bar2";		// error!!
	output(sample.foo2);
	output(sample.bar2);

	std::cout << sample.foo1 << std::endl;
	//std::cout << sample.bar1 << std::endl;	// error...

	return 0;
}
