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

#ifndef __CPP_MODULE_PROPERTY_H__
#define __CPP_MODULE_PROPERTY_H__

namespace cpp_module {

//! simple getter
template <typename T>
struct SimplePropertyGetter
{
	static const T& Get(const T& value) { return value; }
};

//! simple setter
template <typename T>
struct SimplePropertySetter
{
	static void Set(T& value, const T& var) { value = T(var); }
};

//! property
template <typename T>
class Property
{
public:
	Property(T& value) : _value(value) {}
	Property(const Property& ref) : _value(ref._value) {}
	virtual ~Property() {}

	Property<T>& operator = (const Property<T>& ref)
	{
		this->_value = T(ref._value);
		return *this;
	}

protected:
	T&		_value;
};

//! writable property
template <typename T, class Getter = SimplePropertyGetter<T>, class Setter = SimplePropertySetter<T>>
class WritableProperty : public Property<T>, private Getter, private Setter
{
public:
	WritableProperty(T& value) : Property<T>(value) {}
	WritableProperty(const WritableProperty& ref) : Property<T>(ref) {}
	virtual ~WritableProperty() {}

public:
	operator const T& () const { return this->Get(this->_value); }
	const T& operator -> () const { return this->Get(this->_value); }

	WritableProperty<T, Getter, Setter>& operator = (const T& var) { this->Set(this->_value, var); return *this; }
};

//! readonly property
template <typename T, class Getter = SimplePropertyGetter<T>>
class ReadOnlyProperty : public Property<T>, private Getter
{
public:
	ReadOnlyProperty(T& value) : Property<T>(value) {}
	ReadOnlyProperty(const ReadOnlyProperty& ref) : Property<T>(ref) {}
	virtual ~ReadOnlyProperty() {}

public:
	operator const T& () const { return this->Get(this->_value); }
	const T& operator -> () const { return this->Get(this->_value); }
};

}	// end of namespace cpp_module

#endif // __CPP_MODULE_PROPERTY_H__
