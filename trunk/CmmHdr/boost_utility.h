////////////////////////////////////////////////////////////////////////////////////////
// 
// LGCBasic Project
//  
// FileName    : boost_utility.h
// Purpose     : Boost Utility Service
// Version     : 2011-01-15 (16:42) 1.0 Created
//             : 2011-02-27 (22:58) 1.0 Add some comments
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#ifndef _BOOST_UTILITY_H_
#define _BOOST_UTILITY_H_

//Static assertions (compile time assertions)
#include <boost/static_assert.hpp>

//Class next(),  prior()  function templates
#include <boost/utility.hpp>
//Example:
/******************************************************
//Function templates next() and prior()
const std::list<T>::iterator p = get_some_iterator();
const std::list<T>::iterator prev = boost::prior(p);
const std::list<T>::iterator next = boost::next(prev, 2);

//Class noncopyable
// inside one of your own headers ...
#include <boost/utility.hpp>

class ResourceLadenFileSystem : boost::noncopyable {
...


//Function template addressof()
struct useless_type {};
class nonaddressable {
useless_type operator&() const;
};

void f() {
nonaddressable x;
nonaddressable* xp = boost::addressof(x);
// nonaddressable* xpe = &x; // error 
}

*******************************************************/

#include <boost/cast.hpp>
//polymorphic_cast
//polymorphic_downcast
//numeric_cast


//A universally unique identifier
#include <boost/uuid/uuid.hpp>
//Example:
/******************************************************
It is sometimes useful to get at the 16 bytes of a uuid directly.
Typical use is as follows:

boost::uuids::uuid u;
std::vector<char> v(u.size());
std::copy(u.begin(), u.end(), v.begin());
*******************************************************/
#include <boost/uuid/uuid_generators.hpp>
//Example:
/******************************************************
//Nil Generator
The boost::uuids::nil_generator class always generates a nil uuid.

boost::uuids::nil_generator gen;
boost::uuids::uuid u = gen();
assert(u.is_nil() == true);
// or for convenience
boost::uuids::uuid u = boost::uuids::nil_uuid();
assert(u.is_nil() == true);


//String Generator
The boost::uuids::string_generator class generates a uuid from a string.

boost::uuids::string_generator gen;
boost::uuids::uuid u1 = gen("{01234567-89ab-cdef-0123-456789abcdef}");
boost::uuids::uuid u2 = gen(L"01234567-89ab-cdef-0123-456789abcdef");
boost::uuids::uuid u3 = gen(std::string("0123456789abcdef0123456789abcdef"));
boost::uuids::uuid u4 = gen(std::wstring(L"01234567-89ab-cdef-0123-456789abcdef"));


//Name Generator
The boost::uuids::name_generator class generates a name based uuid from a namespace uuid and a name.

boost::uuids::uuid dns_namespace_uuid; // initialize to {6ba7b810-9dad-11d1-80b4-00c04fd430c8}

boost::uuids::name_generator gen(dns_namespace_uuid);
boost::uuids::uuid u = gen("boost.org");

//Random Generator
The boost::uuids::basic_random_generator class generates a random number based uuid from a random number generator (one that conforms to the UniformRandomNumberGenerator concept).

//default construct the random number generator and seed it
boost::uuids::basic_random_generator<boost::mt19937> gen;
boost::uuids::uuid u = gen();

//for convenience boost::uuids::random_generator
//is equivalent to boost::uuids::basic_random_generator<boost::mt19937>
boost::uuids::random_generator gen;
boost::uuids::uuid u = gen();
*******************************************************/
#include <boost/uuid/uuid_io.hpp>
//Stream Operators
//To String

//BOOST_FOREACH macro for easily iterating over the elements of a sequence
#include <boost/foreach.hpp>
//Example
/******************************************************
std::list<int> list_int( /.../ );
BOOST_FOREACH( int i, list_int )
{
    // do something with i
}

std::list<int> list_int( /.../ );
BOOST_REVERSE_FOREACH( int i, list_int )
{
    // do something with i
}
*******************************************************/

namespace lgc
{
    using namespace boost;
    using namespace boost::uuids;
#ifndef BOOST_FOREACH
#define foreach             BOOST_FOREACH
#endif

#ifndef BOOST_REVERSE_FOREACH
#define reverse_foreach     BOOST_REVERSE_FOREACH
#endif

}

#endif

