/**********************************************

Author: Julie Betlach

Adapted from code written by: Terry Caton, tcaton(a)hotmail.com
Project Webpage: http://cajun-jsonapi.sourceforge.net/

Original code parsed files in json format.
Code now parses files in PDI format for a project for Washington University, 
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

***********************************************/

#include "elements.h"
#include "visitor.h"
#include "exception.h"
#include <cassert>
#include <algorithm>

/*  

TODO:
* better documentation

*/

namespace PDI
{

//////////////////
// Element members

class ElementImp
{
public:
   virtual ~ElementImp() {}

   virtual ElementImp* Clone() const = 0;
   virtual ElementType Type() const = 0;

   virtual void Accept(const Element& element, ConstVisitor& visitor) const = 0;
   virtual void Accept(Element& element, Visitor& visitor) = 0;
   virtual void SetName(const std::string& nameIn) = 0;
   virtual const std::string& Name() const = 0;
};

Element::Element() :
   m_pElementImp(0) {
   *this = Null(); // every element is a Null by default
}

Element::Element(const Element& element) :
   m_pElementImp(element.ImpBase().Clone())
{}

Element::~Element() {
   delete m_pElementImp; 
}

Element& Element::operator= (const Element& element) {
   delete m_pElementImp;
   m_pElementImp = element.ImpBase().Clone();
   return *this; 
}

ElementType Element::Type() const {
   return ImpBase().Type(); 
}

Element::Element(ElementImp* elementImp) : 
   m_pElementImp(elementImp)
{}

void Element::Accept(ConstVisitor& visitor) const {
   ImpBase().Accept(*this, visitor);
}

void Element::Accept(Visitor& visitor) {
   ImpBase().Accept(*this, visitor);
}

ElementImp& Element::ImpBase() { 
   assert(m_pElementImp);
   return *m_pElementImp; 
}

const ElementImp& Element::ImpBase() const {
   assert(m_pElementImp);
   return *m_pElementImp;
}

void Element::SetName(const std::string& nameIn) { 
   ImpBase().SetName(nameIn); 
}

const std::string& Element::Name() const { 
   return ImpBase().Name(); 
}
////////////////////
// Element_T members


template <typename ElementTypeT, typename ElementImpTypeT, ElementType TYPE>
class ElementImp_T : public ElementImp
{
public:
   typedef ElementTypeT RealTypeT;
   typedef ElementImpTypeT RealImpTypeT;

   static ElementType Type_i() {
      return TYPE;
   }

   virtual void Accept(const Element& element, ConstVisitor& visitor) const {
      const RealTypeT& realElement = static_cast<const RealTypeT&>(element);
      visitor.Visit(realElement);
   }

   virtual void Accept(Element& element, Visitor& visitor) {
      RealTypeT& realElement = static_cast<RealTypeT&>(element);
      visitor.Visit(realElement);
   }

   // covariant return type does nothing for us here, and we can't do
   //  a real one anyway due to ElementTypeT not being defined yet
   virtual ElementImp* Clone() const { 
      const RealImpTypeT* pRealImpType = static_cast<const RealImpTypeT*>(this);
      return new RealImpTypeT(*pRealImpType);
   }

   virtual ElementType Type() const { return TYPE; }

   virtual void SetName(const std::string& nameIn){ m_sName = nameIn; }
   virtual const std::string& Name() const { return m_sName; }

private:
   std::string m_sName;
};


template <typename ElementImpTypeT>
Element_T<ElementImpTypeT>::Element_T() :
   Element(new ElementImpTypeT()) {
   Type_i();
}

template <typename ElementImpTypeT>
ElementType Element_T<ElementImpTypeT>::Type_i() {
   return ElementImpTypeT::Type_i();
}


//////////////////
// Array members

class ArrayImp : public ElementImp_T<Array, ArrayImp, ARRAY_ELEMENT>
{
public:
   ArrayImp() : m_nDimension(1) {} // suitable default?

   Array::iterator Begin() { return m_Members.begin(); }
   Array::iterator End() { return m_Members.end(); }
   Array::const_iterator Begin() const { return m_Members.begin(); }
   Array::const_iterator End() const { return m_Members.end(); }

   size_t Size() const { return m_Members.size(); }
   bool Empty() const { return m_Members.empty(); }

   size_t Dimension() const { return m_nDimension; }
   void SetDimension(size_t nDimension) { m_nDimension = nDimension; }

   Array::iterator Find(const std::string& name) {
      return std::find_if(m_Members.begin(), m_Members.end(), Finder(name));
   }

   Array::const_iterator Find(const std::string& name) const {
      return std::find_if(m_Members.begin(), m_Members.end(), Finder(name));
   }

   Array::iterator Insert(const Element& element, Array::iterator itWhere) {
      Array::Members::iterator it = std::find_if(m_Members.begin(), m_Members.end(), Finder(element.Name()));
      if (it != m_Members.end())
         throw Exception("Array element already exists: " + element.Name());

      return m_Members.insert(itWhere, element);
   }

   Array::iterator Erase(Array::iterator itWhere) {
      return m_Members.erase(itWhere);
   }

   Element& operator [](const std::string& name) { 
      Array::Members::iterator it = std::find_if(m_Members.begin(), m_Members.end(), Finder(name));
      if (it == m_Members.end())
      {
         it = m_Members.insert(m_Members.end(), Element());
      }

      return *it;
   }

   const Element& operator [](const std::string& name) const {
      Array::Members::const_iterator it = std::find_if(m_Members.begin(), m_Members.end(), Finder(name));
      if (it == m_Members.end())
         throw Exception("Array name not found: " + name);
      return *it;
   }

   void Clear() { m_Members.clear(); }

private:
   class Finder : public std::unary_function<Element, bool>
   {
   public:
      Finder(const std::string& name) : m_name(name) {}
      bool operator () (const Element& element) {
         return element.Name() == m_name;
      }

   private:
      std::string m_name;
   };

   Array::Members m_Members;
   size_t m_nDimension;
};


Array::Array() {}

Array::iterator Array::Begin() {
   return Imp().Begin(); 
}

Array::iterator Array::End() {
   return Imp().End(); 
}

Array::const_iterator Array::Begin() const {
   return Imp().Begin(); 
}

Array::const_iterator Array::End() const {
   return Imp().End();
}

size_t Array::Size() const {
   return Imp().Size(); 
}

bool Array::Empty() const {
   return Imp().Empty(); 
}

size_t Array::Dimension() const {
   return Imp().Dimension(); 
}

void Array::SetDimension(size_t nDimension) {
   Imp().SetDimension(nDimension); 
}

Array::iterator Array::Find(const std::string& name) {
   return Imp().Find(name);
}

Array::const_iterator Array::Find(const std::string& name) const {
   return Imp().Find(name);
}

Array::iterator Array::Insert(const Element& element) {
   return Imp().Insert(element, End());
}

Array::iterator Array::Insert(const Element& element, Array::iterator itWhere) {
   return Imp().Insert(element, itWhere);
}

Element& Array::operator [] (const std::string& name) {
   return Imp()[name]; 
}

const Element& Array::operator [] (const std::string& name) const {
   return Imp()[name]; 
}

void Array::Clear() {
   Imp().Clear();
}

///////////////
// Null members


class NullImp : public ElementImp_T<Null, NullImp, NULL_ELEMENT>
{};



////////////////////////
// DisplayElement members

class DisplayElementImp : public ElementImp_T<DisplayElement, DisplayElementImp, DISPLAY_ELEMENT>
{
public:
   DisplayElementImp& operator = (const std::string& s) { 
      m_sValue = s; 
      m_iSizeToExtractFromBuffer = 1;
      return *this;
   }

   operator std::string&() { return m_sValue; }
   operator const std::string&() const { return m_sValue; }

private:
   std::string m_sValue;
   unsigned int m_iSizeToExtractFromBuffer; // Size read in from the PDI file which will be used by instruction
   // class in order to extract a field from the buffer read in by Wireshark.
   // For some types this size will represent bits.  For others it may be bytes.
   // To keep separation of logic for PDI instructions from the logic of the PDI parser, this code will just 
   // pass the value along, and will not have different logic for bits versus bytes.
};


DisplayElement::DisplayElement(const std::string& s)
{
   //Imp().SetValue(t);
   Imp().operator=(s);
}

DisplayElement& DisplayElement::operator = (const std::string& s) {
   Imp().operator=(s);
   return *this;
}

DisplayElement::operator const std::string&() const {
   return Imp().operator const std::string&();
}

DisplayElement::operator std::string&() {
   return Imp().operator std::string&();
}


} // End namespace
