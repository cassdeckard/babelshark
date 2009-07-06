
#ifndef SINGLETON_H
#define SINGLETON_H

#include <assert.h>

// ================================================================================
/**
 \class Singleton
 \brief Implements the Singleton pattern (see Design Patterns - GoF)

  This Singleton class provides lazy class construction, as well as explicit 
  functionality to release the Singleton resource. In addition, if the user
  fails to release the Singleton explicitly, it will be released automatically
  when the application shuts down.

  The internal implementation is perhaps a bit clumsy (the Create/Destroy 
  functions and the friend declaration, specifically) due to the requirement that 
  this Singleton class be backwards compatible with the previous implementation 
  this is replacing.

*/
// ================================================================================
template<class T>
class Singleton
{
public:
   class SingletonHelper;

   static T& Instance();
   static void Release();

   __declspec(noinline) static SingletonHelper& HelperInstance();

private:
   static void Create(T* volatile& pT );
   static void Destroy(T* volatile& pT);
};


// ================================================================================
/**
 \class SingletonHelper
 \brief Implements the Singleton pattern (see Design Patterns - GoF)

  Intended to be instantiated as a static variable inside of a Singleton function,
  this class ensures that the instance pointer will be released, even if the user
  fails to do so explicitly (the C++ Runtime will call the SingletonHelper 
  destructor at shutdown, which will call Release and delete the pointer if not 
  null).

*/
// ================================================================================
template<class T>
class Singleton<T>::SingletonHelper
{
   public:
      SingletonHelper();
      ~SingletonHelper();
      
      T* Instance();
      void Release();
            
   private:
      T* volatile m_pObjPtr;
};


//==============================================================================
/**
 \fn  Singleton<T>::Instance()
 \brief  Returns the SingletonHelper's class instance.

  @return T* 
*/
//==============================================================================

template<class T>
T& Singleton<T>::Instance()
{
   return *HelperInstance().Instance();
}


//==============================================================================
/**
 \fn  Singleton<T>::Release()
 \brief  Instructs the SingletonHelper to release its instance, if it has one.

 @return void
*/
//==============================================================================
template<class T>
void Singleton<T>::Release()
{
   HelperInstance().Release();
}


//==============================================================================
/**
 \fn  Singleton<T>::HelperInstance()
 \brief  Returns a reference to a static SingletonHelper class. 

 A static SingletonHelper instance is declared (ensured by the compiler that
 only one will be created), and is returned by reference.

 @return Singleton<T>::SingletonHelper&
*/
//==============================================================================

template<class T>
typename Singleton<T>::SingletonHelper& Singleton<T>::HelperInstance()
{
   static SingletonHelper* pHelper = 0;

   if (pHelper == 0)
   {
      static SingletonHelper helper;
      pHelper = &helper;
   }
   
   return *pHelper;
}


//==============================================================================
/**
 \fn  Singleton<T>::Create()
 \brief  An object of type T is allocated, and the reference to pointer 
 passed in is set to this new object. 

 The 
 @param T*& pT - the instance pointer to be initialized
 @return void
*/
//==============================================================================
template<class T>
void Singleton<T>::Create(T* volatile& pT )
{
   assert(!pT);
   pT = new T; 
}


//==============================================================================
/**
 \fn  Singleton<T>::Destroy()
 \brief  The object pointed to by the reference to pointer parameter is 
 deallocated, and the pointer is set to null.

 @param T*& pT - the instance pointer to be destroyed
 @return void
*/
//==============================================================================
template<class T>
void Singleton<T>::Destroy(T* volatile& pT) 
{
   assert(pT);
   delete pT; pT = 0; 
}


//==============================================================================
/**
 \fn  Singleton<T>::SingletonHelper::SingletonHelper()
 \brief  Constructor

*/
//==============================================================================
template<class T>
Singleton<T>::SingletonHelper::SingletonHelper() : 
   m_pObjPtr(0)
{
}


//==============================================================================
/**
 \fn  Singleton<T>::SingletonHelper::~SingletonHelper()
 \brief  Destructor

 Calls release, ensuring the instance pointer is deleted if it points to a 
 valid object

*/
//==============================================================================
template<class T>
Singleton<T>::SingletonHelper::~SingletonHelper()
{
   Release();
}


//==============================================================================
/**
 \fn  Singleton<T>::SingletonHelper::Instance()
 \brief  Constructor

 If the class instance does not exist, it will be created and returned; if it
 does exist, the existing pointer will be returned.

 @return T*
*/
//==============================================================================

template<class T>
T* Singleton<T>::SingletonHelper::Instance()
{ 
	if (m_pObjPtr == 0)
	{
		Singleton::Create(m_pObjPtr);
	}

	return m_pObjPtr; 
}


//==============================================================================
/**
 \fn  Singleton<T>::SingletonHelper::Release()
 \brief  Destroys the instance pointer if it exists. 

 @return void
*/
//==============================================================================
template<class T>
void Singleton<T>::SingletonHelper::Release()
{
   if (m_pObjPtr != 0)
   {
      Singleton::Destroy(m_pObjPtr);
   }
   m_pObjPtr = 0;
}


#endif
