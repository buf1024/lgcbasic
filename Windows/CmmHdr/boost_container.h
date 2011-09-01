////////////////////////////////////////////////////////////////////////////////////////
// 
// LGCBasic Project  
//  
// FileName    : boost_container.h
// Purpose     : Boost Container Service
// Version     : 2011-01-15 (16:49) 1.0 Created
//               2011-03-02 (14:57) 1.1 Add some comments
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#ifndef _BOOST_CONTAINER_H_
#define _BOOST_CONTAINER_H_

//Bidirectional maps
#include <boost/bimap/bimap.hpp>
//A Bimap is a data structure that represents bidirectional relations between elements of
//two collections. The container is designed to work as two opposed STL maps. A bimap
//between a collection X  and a collection Y can be viewed as a map from X to Y
//(this view will be called the left map view) or as a map from Y  to X (known as the right
//map view). Additionally, the bimap can also be viewed as a set of relations between X and 
//Y (named the collection of relations view). 
//Example:
/**********************************************************************************
//Lets define a bidirectional map between integers and strings:
typedef boost::bimap< int, std::string > bm_type;
bm_type bm;

The left map view
bm.left works like a std::map<int, std::string >

The right map view
bm.right works like a std::map<std::string, int >
***********************************************************************************/


//unordered associative containers
#include <boost/unordered_map.hpp>

//generic container for single values of different value types
#include <boost/any.hpp>
//There are times when a generic (in the sense of general as opposed to template-based
//programming) type is needed: variables that are truly variable, accommodating values
//of many other more specific types rather than C++'s normal strict and static types.
//We can distinguish three basic kinds of generic type:
//Eample
/**********************************************************************************
boost::any a;
a=std::string("A string");
a=42;
a=3.1415;

std::string s=boost::any_cast<std::string>(a);
// throw boost::bad_any_cast.
***********************************************************************************/

//generic, stack-based discriminated union container,
#include <boost/variant.hpp>
//Example
/**********************************************************************************
//a variant can hold int, std::string, or double
boost::variant<int,std::string,double> my_first_variant;

boost::variant<int,std::string,double> my_first_variant("Hello world");
my_first_variant=24;
my_first_variant=2.52;
my_first_variant="Fabulous!";
my_first_variant=0;

assert(boost::get<int>(my_first_variant)==0);
***********************************************************************************/

//Ease definition of functions returning multiple values, and more
#include <boost/tuple/tuple.hpp>
//A tuple (or n-tuple) is a fixed size collection of elements. Pairs, triples, quadruples
//etc. are tuples. In a programming language, a tuple is a data object containing other
//objects as elements. These element objects may be of different types. 
//Example
/**********************************************************************************
boost::tuple<int,double,std::string>   triple(42,3.14,"My first tuple!");

boost::tuples::tuple<int,double> get_values()
{ 
    return boost::make_tuple(6,12.0);
}

boost::tuple<int,double,std::string>
triple(42,3.14,"The amazing tuple!");
int i=boost::tuples::get<0>(triple);
double d=triple.get<1>();
std::string s=boost::get<2>(triple);
***********************************************************************************/
namespace lgc
{
    using namespace boost;
}

#endif


