/***********************************************

Author: Julie Betlach

Adapted from code written by: Terry Caton, tcaton(a)hotmail.com
Project Webpage: http://cajun-jsonapi.sourceforge.net/

Original code parsed files in json format.
Code now parses files in PDI format for a project for Washington University, 
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

*************************************************/

#pragma once

#include "elements.h"
#include "visitor.h"

namespace PDI
{


class Writer : private ConstVisitor
{
public:
   static void Write(const Element& elementRoot, std::ostream& ostr);
      
private:
   Writer(std::ostream& ostr) :
      m_ostr(ostr),
      m_nTabDepth(0) {}

   virtual void Visit(const Array& array);
   virtual void Visit(const DisplayElement& string);
   virtual void Visit(const Null& null);

   std::ostream& m_ostr;
   int m_nTabDepth;
};


} // End namespace