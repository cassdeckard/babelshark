/**********************************************

Author: Julie Betlach

Adapted from code written by: Terry Caton, tcaton(a)hotmail.com
Project Webpage: http://cajun-jsonapi.sourceforge.net/

Original code parsed files in json format.
Code now parses files in PDI format for a project for Washington University, 
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

File Name: Elements.h

File Description: The Elements.h file is a part of the PDI parser.  It provides the implementation
of the different element types: ARRAY_ELEMENT, DISPLAY_ELEMENT, and NULL_ELEMENT.
***********************************************/

#pragma once

#include <vector>
#include <list>
#include <string>


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

/**********************
Class Name: Element
Class Description: This class is the base class for the element type classes.
The Element class and ElementImp class follow the Pimple Design Pattern.
The majority of this class existed in the CAJUN JSON parser.  However, it has been
modified to suit our needs as explained below.

Each DisplayElement has three components: Name, Type, Size.
The interface for the SetName function (used to place the name into the member variable) 
and the Name function (used to obtain the value of the member variable) have been defined here.
The actual member variable that holds the Name is not in the Element class.  It is in the
ElementImp_T class.  This was done because the Element class did not need to know about the
member variable.
***********************/
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

/**********************
Class Name: Element_T
Class Description: This class is a template class for the element type classes.
This class existed in the CAJUN JSON parser and has not changed.
***********************/
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
// Array - mimics std::list<Element>, the array contents are 
// effectively heterogeneous thanks to the Element base class
/**********************
Class Name: Array
Class Description: The Array class defines the interface to the ArrayImp class.
The Array class and ArrayImp class follow the Pimple Design Pattern.
The majority of this class existed in the CAJUN JSON parser as the OBJECT_ELEMENT.  However, it has been
modified to suit our needs as explained below.

The list is now a list of elements.  Previously, it was a list of member structs which contained both a
name and an element.  The concept of the struct was removed because the name field was moved into the element.
This Array class does not really hold items in the normal Array sense (in that you have item[0], item[1], etc.)
Instead it contains an ordered list of elements.

The concept of dimension was added to this class.  Our PDI format allows the user to specify a number after the
closing bracket which specifies the dimension of the array.  Rather than storing extra elements in the array,
it was more efficient just to store the dimension read in from the file.  When an InstructionSet is created
from the Array element, the dimension will be passed into its constructor and it will appropriately handle 
dealing with the buffer of bits being sniffed by Wireshark.
***********************/
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

   size_t Size() const;  // This is the number of elements in the array.
   bool Empty() const;

   size_t Dimension() const;  // This is the dimension read in from the file.
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


/**********************
Class Name: DisplayElement
Class Description: The DisplayElement class defines the interface to the DisplayElementImp class.
The DisplayElement class and DisplayElementImp class follow the Pimple Design Pattern.
The majority of this class existed in the CAJUN JSON parser as the OBJECT_STRING.  However, it has been
modified to suit our needs as explained below.

The class has a very similar interface as before, however, the names of the class and the functions have
been changed to be more clear about the new functionality of the class, to support DisplayElements which
consist of a display type and size.
***********************/
class DisplayElementImp;
class DisplayElement : public Element_T<DisplayElementImp>
{
public:
   DisplayElement(const std::string& s = std::string());
   DisplayElement& operator = (const std::string& s);

   operator const std::string&() const;
   operator std::string&();
};



/**********************
Class Name: Null
Class Description: The Null class defines the interface to the NullImp class.
The Null class and NullImp class follow the Pimple Design Pattern.
This class existed in the CAJUN JSON parser.  It has not been modified.

JSON supported Null elements.  However, our PDI language does not.  However, this class was
retained so that it could be used as a default type prior to us knowing the element type.
***********************/
class NullImp;
class Null : public Element_T<NullImp>
{};




} // End namespace
