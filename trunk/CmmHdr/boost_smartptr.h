////////////////////////////////////////////////////////////////////////////////////////
//  
// LGCBasic Project
//  
// FileName    : boost_smartptr.h
// Purpose     : Boost Smart_ptr Service
// Version     : 2011-01-15 (16:32) 1.0 Created
//             : 2011-02-27 (22:29) 1.1 Add some comments
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#ifndef _BOOST_SMARTPTR_H_
#define _BOOST_SMARTPTR_H_

//Simple sole ownership of single objects. Noncopyable.
#include <boost/scoped_ptr.hpp>

//Simple sole ownership of arrays. Noncopyable.
#include <boost/scoped_array.hpp>

//Object ownership shared among multiple pointers.
#include <boost/shared_ptr.hpp>

//Array ownership shared among multiple pointers.
#include <boost/shared_array.hpp>

//Shared ownership of objects with an embedded reference count.
#include <boost/intrusive_ptr.hpp>

//Non-owning observers of an object owned by shared_ptr.
#include <boost/weak_ptr.hpp>
#include <boost/make_shared.hpp>
//Consistent use of shared_ptr  can eliminate the need to use
//an explicit delete, but alone it provides no support in avoiding
//explicit new. There have been repeated requests from users for
//a factory function that creates an object of a given type and
//returns a shared_ptr to it.
//Example
/**********************************************************************************
boost::shared_ptr<std::string> x = boost::make_shared<std::string>("hello, world!");
std::cout << *x;
***********************************************************************************/



namespace lgc
{
    using namespace boost;
}


#endif

