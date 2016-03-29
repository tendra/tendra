/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <exception>
#include <new>
#include <typeinfo>

using namespace std;

/*
 * Exception base class
 *
 * This routines give the definitions of the member function of the
 * exception class.
 */
exception::exception() throw ()
{
	return;
}

exception::exception(const exception &) throw ()
{
	return;
}

exception &
exception::operator = (const exception &) throw ()
{
	return *this;
}

exception::~exception() throw ()
{
	return;
}

const char *
exception::what() const throw ()
{
	return "exception";
}

/*
 * Bad exception class
 *
 * This routines give the definitions of the member function of the
 * bad_exception class.
 */
bad_exception::bad_exception() throw ()
{
	return;
}

bad_exception::bad_exception(const bad_exception &) throw ()
{
	return;
}

bad_exception &
bad_exception::operator = (const bad_exception &) throw ()
{
	return *this;
}

bad_exception::~bad_exception() throw ()
{
	return;
}

const char *bad_exception::what() const throw ()
{
	return "bad_exception";
}

/*
 * Bad allocation exception class
 *
 * This routines give the definitions of the member function of the
 * bad_alloc class.
 */
bad_alloc::bad_alloc() throw ()
{
	return;
}

bad_alloc::bad_alloc(const bad_alloc &) throw ()
{
	return;
}

bad_alloc &
bad_alloc::operator = (const bad_alloc &) throw ()
{
	return *this;
}

bad_alloc::~bad_alloc() throw ()
{
	return;
}

const char *
bad_alloc::what() const throw ()
{
	return "bad_alloc";
}

/*
 * Bad dynamic cast exception class
 *
 * This routines give the definitions of the member function of the
 * bad_cast class.
 */
bad_cast::bad_cast() throw ()
{
	return;
}

bad_cast::bad_cast(const bad_cast &) throw ()
{
	return;
}

bad_cast &
bad_cast::operator = (const bad_cast &) throw ()
{
	return *this;
}

bad_cast::~bad_cast() throw ()
{
	return;
}

const char *
bad_cast::what() const throw ()
{
	return "bad_cast";
}

/*
 * Bad typeid exception class
 *
 * This routines give the definitions of the member function of the
 * bad_typeid class.
 */
bad_typeid::bad_typeid() throw ()
{
	return;
}

bad_typeid::bad_typeid(const bad_typeid &) throw ()
{
	return;
}

bad_typeid &
bad_typeid::operator = (const bad_typeid &) throw ()
{
	return *this;
}

bad_typeid::~bad_typeid() throw ()
{
	return;
}

const char *
bad_typeid::what() const throw ()
{
	return "bad_typeid";
}

