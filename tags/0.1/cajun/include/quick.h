/******************************************************************************

Author: Julie Betlach

Adapted from code written by: Terry Caton, tcaton(a)hotmail.com
Project Webpage: http://cajun-jsonapi.sourceforge.net/

Original code parsed files in json format.
Code now parses files in PDI format for a project for Washington University, 
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

classes: QuickInterpreter
         QuickBuilder

The classes in this file provide an alternative interface for very quickly 
extracting or  compiling data into a JSON document structure. They are useful 
when the structure of a document is rigid and well-known, which is often the 
case. 

QuickInterpreter allows quick, read-only access to an existing document 
structure. For examples, given the document...

{
   "XYZ" : {
         "ABC" : [ 1 ]
   }
}

QuickInterpreter interpreter(elemRoot); // elemRoot containing above structure
const Array& array = interpreter["XYZ"];
const Array& array = interpreter["XYZ"]["ABC"];
const Number& num = interpreter["XYZ"]["ABC"][0];

QuickBuilder allows building the above structure with one line of code:

QuickBuilder builder(elemRoot); // elemRoot being an empty Element
builder["XYZ"][ABC][0] = Number(1);

******************************************************************************/

#pragma once

#include "elements.h"


namespace PDI
{


class QuickInterpreter
{
public:
   QuickInterpreter(const Element& element) :
      m_Element(element) {}

   QuickInterpreter operator[] (const std::string& key) const {
      const Array& obj = As<Array>();
      return obj[key];
   }

   operator const Element& () const { return m_Element; }

   template <typename ElementTypeT>
   const ElementTypeT& As() const { return PDI_cast<const ElementTypeT&>(m_Element); }

private:
   const Element& m_Element;
};


class QuickBuilder
{
public:
   QuickBuilder(Element& element) :
      m_Element(element) {}

   QuickBuilder operator[] (const std::string& key) {
      Array& obj = Convert<Array>();
      return obj[key];
   }

   QuickBuilder& operator = (const Element& element) {
      m_Element = element;
      return *this;
   }

   operator Element& () { return m_Element; }

   template <typename ElementTypeT>
   ElementTypeT& As() { return PDI_cast<ElementTypeT&>(m_Element); }

   template <typename ElementTypeT>
   ElementTypeT& Convert() {
      // we want an ElementTypeT. make it one if it's not.
      try {
         return As<ElementTypeT>();
      }
      catch (Exception&) {
         m_Element = ElementTypeT();
         return As<ElementTypeT>();
      }
   }

private:
   Element& m_Element;
};

}