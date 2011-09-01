////////////////////////////////////////////////////////////////////////////////////////
// 
// LGCBasic Project
//  
// FileName    : boost_string.h
// Purpose     : Boost String Service
// Version     : 2011-01-15 (16:56) 1.0 Created
//             : 2011-02-27 (22:13) 1.1 Add some additional heads & example
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////
#ifndef _BOOST_STRING_H_
#define _BOOST_STRING_H_

//lexical_cast  class template
#include <boost/lexical_cast.hpp>
//when we need a value must be converted to a literal text form,
//Such as an int  represented as a string, or vice-versa.
//Example:
/*****************************************************
    using boost::lexical_cast;
    using boost::bad_lexical_cast;

    std::vector<short> args;

    while(*++argv)
    {
        try
        {
            args.push_back(lexical_cast<short>(*argv));
        }
        catch(bad_lexical_cast &)
        {
            args.push_back(0);
        }
    }

******************************************************/

//Type-safe 'printf-like' format operations
#include <boost/format.hpp>
//A format object is constructed from a format-string,
//and is then given arguments through repeated calls to operator%.
//Each of those arguments are then converted to strings, who are
//in turn combined into one string, according to the format-string.
//Example:
/*****************************************************
cout << boost::format("writing %1%,  x=%2% : %3%-th try") % "toto" % 40.23 % 50; 
  // prints "writing toto,  x=40.230 : 50-th try"

format fmter("%2% %1%");
fmter % 36; fmter % 77;
// You can take the string result :
string s  = fmter.str();

******************************************************/


//String algorithms library
#include <boost/algorithm/string.hpp>
//The String Algorithm Library provides a generic implementation of
//string-related algorithms which are missing in STL. It is an extension
//to the algorithms library of STL and it includes trimming, case
//conversion, predicates and find/replace functions. All of them come in
//different variants so it is easier to choose the best fit for a particular need. 
//Example:
/*****************************************************
//Case conversion
string str1("HeLlO WoRld!");
to_upper(str1); // str1=="HELLO WORLD!"

to_upper() and to_lower() convert the case of characters in a string
using a specified locale. 

//Predicates and Classification
bool is_executable( string& filename )
{
    return 
        iends_with(filename, ".exe") ||
        iends_with(filename, ".com");
}

//Trimming
string str1="     hello world!     ";
string str2=trim_left_copy(str1);   // str2 == "hello world!     "
string str3=trim_right_copy(str1);  // str3 == "     hello world!"
trim(str1);                         // str1 == "hello world!"

string phone="00423333444";
// remove leading 0 from the phone number
trim_left_if(phone,is_any_of("0")); // phone == "423333444"

//Find algorithms
char text[]="hello dolly!";
iterator_range<char*> result=find_last(text,"ll");

transform( result.begin(), result.end(), result.begin(), bind2nd(plus<char>(), 1) );
// text = "hello dommy!"            

to_upper(result); // text == "hello doMMy!"

// iterator_range is convertible to bool
if(find_first(text, "dolly"))
{
cout << "Dolly is there" << endl;
}

//Replace Algorithms
string str1="Hello  Dolly,   Hello World!"
replace_first(str1, "Dolly", "Jane");      // str1 == "Hello  Jane,   Hello World!"
replace_last(str1, "Hello", "Goodbye");    // str1 == "Hello  Jane,   Goodbye World!"
erase_all(str1, " ");                      // str1 == "HelloJane,GoodbyeWorld!"
erase_head(str1, 6);                       // str1 == "Jane,GoodbyeWorld!"


******************************************************/

//Break of a string or other character sequence into a series of tokens
#include <boost/tokenizer.hpp>
//The boost Tokenizer package provides a flexible and easy to use way to
//break of a string or other character sequence into a series of tokens. 
//Example
/*****************************************************
int main(){
    using namespace std;
    using namespace boost;
    string s = "This is,  a test";
    tokenizer<> tok(s);
    for(tokenizer<>::iterator beg=tok.begin(); beg!=tok.end();++beg){
        cout << *beg << "\n";
    }
}

The output from simple_example_1 is:

This
is
a
test
******************************************************/

//boost/regex.hpp need to comiple additional, so not include here

namespace lgc
{
    using namespace boost;
}



#endif


