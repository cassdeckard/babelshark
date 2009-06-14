/**********************************************

Author: Julie Betlach

Adapted from code written by: Terry Caton, tcaton(a)hotmail.com
Project Webpage: http://cajun-jsonapi.sourceforge.net/

Original code parsed files in json format.
Code now parses files in PDI format for a project for Washington University, 
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

***********************************************/

#pragma once

#include <vector>
#include <list>
#include <string>


/*  

TODO:
* better documentation

*/

namespace PDI
{

class Visitor;
class ConstVisitor;

enum ElementType
{
   ARRAY_ELEMENT,
   DISPLAY_ELEMENT,
   NULL_ELEMENT
};


////////////////////////////////////////////////////////////////////////
// base class - provides little useful in client code except constructor

class ElementImp;
class Element
{
public:
   // note: nothing virtual in here! and only one (1) pointer member
   Element();
   Element(const Element& element);
   ~Element();

   Element& operator= (const Element& element);
   
   ElementType Type() const;

   // const & non-const visitor interfaces
   void Accept(Visitor& visitor);
   void Accept(ConstVisitor& visitor) const;

   void SetName(const std::string& nameIn);
   const std::string& Name() const;

protected:
   Element(ElementImp* elementImp);

   ElementImp& ImpBase();
   const ElementImp& ImpBase() const;

private:
   ElementImp* m_pElementImp;
};


///////////////////////////////////////////////////////////////////////////////
// template base class for all "concrete" element types. employs "curiously 
// recursive template pattern", also provides little interface used in client 
// code 

template <typename ElementImpTypeT>
class Element_T : public Element
{
public:
   static ElementType Type_i();

protected:
   Element_T();

   //  return type is covariant with ImpBase(), but compiler doesn't know it (can't forward-declare inheritance)
   ElementImpTypeT& Imp() { return static_cast<ElementImpTypeT&>(ImpBase()); }
   const ElementImpTypeT& Imp() const { return static_cast<const ElementImpTypeT&>(ImpBase()); }
};



/////////////////////////////////////////////////////////////////////////////////
// Array - mimics std::map<std::string, Element>, except the array contents are 
// effectively heterogeneous thanks to the Element base class

class ArrayImp;
class Array : public Element_T<ArrayImp>
{
public:
   typedef std::list<Element> Members; // map faster, but does not preserve order
   typedef Members::iterator iterator;
   typedef Members::const_iterator const_iterator;

   Array(); // necessary, or we get linker errors... ?

   iterator Begin();
   iterator End();
   const_iterator Begin() const;
   const_iterator End() const;

   size_t Size() const;
   bool Empty() const;

   size_t Dimension() const;
   void SetDimension(size_t nDimension);

   iterator Find(const std::string& name);
   const_iterator Find(const std::string& name) const;

   iterator Insert(const Element& element);
   iterator Insert(const Element& element, iterator itWhere);
   iterator Erase(iterator itWhere);

   Element& operator [] (const std::string& name);
   const Element& operator [] (const std::string& name) const;

   void Clear();
};



class StringImp;
class DisplayElement : public Element_T<StringImp>
{
public:
   DisplayElement(const std::string& s = std::string());
   DisplayElement& operator = (const std::string& s);

   operator const std::string&() const;
   operator std::string&();
};




class NullImp;
class Null : public Element_T<NullImp>
{};




} // End namespace
