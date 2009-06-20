/**********************************************

Author: Julie Betlach

Adapted from code written by: Terry Caton, tcaton(a)hotmail.com
Project Webpage: http://cajun-jsonapi.sourceforge.net/

Original code parsed files in json format.
Code now parses files in PDI format for a project for Washington University, 
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

***********************************************/

#pragma once

#include "elements.h"

namespace PDI
{


class Visitor
{
public:
   virtual void Visit(Array& array) = 0;
   virtual void Visit(DisplayElement& string) = 0;
   virtual void Visit(Null& null) = 0;
};

class ConstVisitor
{
public:
   virtual void Visit(const Array& array) = 0;
   virtual void Visit(const DisplayElement& string) = 0;
   virtual void Visit(const Null& null) = 0;
};


}