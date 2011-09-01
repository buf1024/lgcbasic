////////////////////////////////////////////////////////////////////////////////////////
// 
// LGCBasic Project
// 
// FileName    : Singleton.h
// Purpose     : Sington supper class
// Version     : 2011-02-27 (21:00) 1.0 Created
// Author      : heidong
// Contact     : buf1024@gmail.com
// Copyright(c): HEIDONG
////////////////////////////////////////////////////////////////////////////////////////

#ifndef _SINGLETON_H_ 
#define _SINGLETON_H_


/**Sington supper class.
*Use the static functions to obtain an instance or release resource.
*Not to initialize it when you want it to serve as a sington.
*/
template <typename TheClass>
class Singleton
{
protected:
    Singleton()
    {

    }
public:
    virtual ~Singleton()
    {

    }
public:
    /**The pointer form of sington
    * @return an unique sington
    */
    static TheClass* GetInstPtr()
    {
        if (sm_pInst == NULL)
        {
            sm_pInst = new TheClass;
        }
        return sm_pInst;
    }
    /**The reference form of sington
    * @return an unique sington
    */
    static TheClass& GetInst()
    {
        if (sm_pInst == NULL)
        {
            sm_pInst = new TheClass;
        }
        return *sm_pInst;
    }
    /**Release the sington*/
    static void ReleaseRC()
    {
        if (sm_pInst != NULL)
        {
            delete sm_pInst;
            sm_pInst = NULL;
        }
    }
private:
    static TheClass* sm_pInst;
};

template <typename TheClass>
TheClass* Singleton<TheClass>::sm_pInst = NULL;


#endif