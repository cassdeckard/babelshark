/**********************************************

License: BSD
Project Webpage: http://cajun-jsonapi.sourceforge.net/
Author: Terry Caton, tcaton(a)hotmail.com
Modifications for Wireshark Dissector Project: Julie Betlach, julie.betlach(a)gmail.com

TODO: additional documentation. 

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
   virtual std::string GetName() const = 0;
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

// I don't know what to do for these next two functions.
void Element::SetName(const std::string& nameIn){ ImpBase().SetName(nameIn); }
std::string Element::GetName() const { return ImpBase().GetName(); }

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

   virtual void SetName(const std::string& nameIn){ name = nameIn; }
   virtual std::string GetName() const { return name; }
private:
   std::string name;
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


/////////////////
// Array members

class ArrayImp : public ElementImp_T<Array, ArrayImp, ARRAY_ELEMENT>
{
public:
   Array::iterator Begin() { return m_Elements.begin(); }
   Array::iterator End() { return m_Elements.end(); }
   Array::const_iterator Begin() const { return m_Elements.begin(); }
   Array::const_iterator End() const { return m_Elements.end(); }
   
   Array::iterator Insert(const Element& element, Array::iterator itWhere) { 
      return m_Elements.insert(itWhere, element);
   }

   Array::iterator Erase(Array::iterator itWhere) { 
      return m_Elements.erase(itWhere);
   }

   void Resize(size_t newSize) {
      m_Elements.resize(newSize);
   }

   size_t Size() const { return m_Elements.size(); }
   bool Empty() const { return m_Elements.empty(); }

   Element& operator[] (size_t index) {
      if (index >= m_Elements.size())
         throw Exception("Array out of bounds");
      Array::iterator it = m_Elements.begin();
      std::advance(it, index);
      return *it; 
   }
   const Element& operator[] (size_t index) const {
      if (index >= m_Elements.size())
         throw Exception("Array out of bounds");
      Array::const_iterator it = m_Elements.begin();
      std::advance(it, index);
      return *it; 
   }

private:
   Array::Elements m_Elements;
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

Array::iterator Array::Insert(const Element& element) {
   return Imp().Insert(element, End()); 
}

Array::iterator Array::Insert(const Element& element, Array::iterator itWhere) {
   return Imp().Insert(element, itWhere); 
}

Array::iterator Array::Erase(Array::iterator itWhere) {
   return Imp().Erase(itWhere); 
}

void Array::Resize(size_t newSize) {
   Imp().Resize(newSize); 
}

size_t Array::Size() const {
   return Imp().Size(); 
}

bool Array::Empty() const {
   return Imp().Empty();
}

Element& Array::operator [] (size_t index) {
   return Imp()[index]; 
}

const Element& Array::operator [] (size_t index) const {
   return Imp()[index]; 
}


//////////////////
// Object members

class ObjectImp : public ElementImp_T<Object, ObjectImp, OBJECT_ELEMENT>
{
public:
   Object::iterator Begin() { return m_Members.begin(); }
   Object::iterator End() { return m_Members.end(); }
   Object::const_iterator Begin() const { return m_Members.begin(); }
   Object::const_iterator End() const { return m_Members.end(); }

   size_t Size() const { return m_Members.size(); }
   bool Empty() const { return m_Members.empty(); }

   Object::iterator Find(const std::string& name) {
      return std::find_if(m_Members.begin(), m_Members.end(), Finder(name));
   }

   Object::const_iterator Find(const std::string& name) const {
      return std::find_if(m_Members.begin(), m_Members.end(), Finder(name));
   }

   Object::iterator Insert(const Object::Member& member, Object::iterator itWhere) {
      Object::Members::iterator it = std::find_if(m_Members.begin(), m_Members.end(), Finder(member.name));
      if (it != m_Members.end())
         throw Exception("Object member already exists: " + member.name);

      return m_Members.insert(itWhere, member);
   }

   Object::iterator Erase(Object::iterator itWhere) {
      return m_Members.erase(itWhere);
   }

   Element& operator [](const std::string& name) { 
      Object::Members::iterator it = std::find_if(m_Members.begin(), m_Members.end(), Finder(name));
      if (it == m_Members.end())
      {
         it = m_Members.insert(m_Members.end(), Object::Member());
         it->name = name;
      }
      return it->element;      
   }

   const Element& operator [](const std::string& name) const {
      Object::Members::const_iterator it = std::find_if(m_Members.begin(), m_Members.end(), Finder(name));
      if (it == m_Members.end())
         throw Exception("Object name not found: " + name);
      return it->element;
   }

   void Clear() { m_Members.clear(); }

private:
   class Finder : public std::unary_function<Object::Member, bool>
   {
   public:
      Finder(const std::string& name) : m_name(name) {}
      bool operator () (const Object::Member& member) {
         return member.name == m_name;
      }

   private:
      std::string m_name;
   };

   Object::Members m_Members;
};


Object::Object() {}

Object::iterator Object::Begin() {
   return Imp().Begin(); 
}

Object::iterator Object::End() {
   return Imp().End(); 
}

Object::const_iterator Object::Begin() const {
   return Imp().Begin(); 
}

Object::const_iterator Object::End() const {
   return Imp().End();
}

size_t Object::Size() const {
   return Imp().Size(); 
}

bool Object::Empty() const {
   return Imp().Empty(); 
}

Object::iterator Object::Find(const std::string& name) {
   return Imp().Find(name);
}

Object::const_iterator Object::Find(const std::string& name) const {
   return Imp().Find(name);
}

Object::iterator Object::Insert(const Member& member) {
   return Imp().Insert(member, End());
}

Object::iterator Object::Insert(const Member& member, Object::iterator itWhere) {
   return Imp().Insert(member, itWhere);
}

Element& Object::operator [] (const std::string& name) {
   return Imp()[name]; 
}

const Element& Object::operator [] (const std::string& name) const {
   return Imp()[name]; 
}

void Object::Clear() {
   Imp().Clear();
}

///////////////
// Null members


class NullImp : public ElementImp_T<Null, NullImp, NULL_ELEMENT>
{};



////////////////////////
// String members

class StringImp : public ElementImp_T<String, StringImp, STRING_ELEMENT>
{
public:
   StringImp& operator = (const std::string& s) { 
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


String::String(const std::string& s)
{
   //Imp().SetValue(t);
   Imp().operator=(s);
}

String& String::operator = (const std::string& s) {
   Imp().operator=(s);
   return *this;
}

String::operator const std::string&() const {
   return Imp().operator const std::string&();
}

String::operator std::string&() {
   return Imp().operator std::string&();
}


} // End namespace
