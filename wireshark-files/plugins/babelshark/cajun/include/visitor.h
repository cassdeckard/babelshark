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

namespace PDI
{

/** The class Visitor is an abstract base class.
  * Classes which are derived from this class are allowed to modify
  * the parameters passed into the Visit functions.  However, if
  * you don't need to modify the parameters, then derive from the
  * ConstVisitor class.
  *
  * Design Pattern: Visitor
  * Design Pattern Role: Visitor
  * Other Participants: 
  *    There is no ConcreteVisitor class.  The Vistor class was provided for future growth.
  *    The abstract Element class plays the Element role.
  *    The Array class plays the ConcreteElement role.
  *    The DisplayElement class plays the ConcreteElement role.
  *    The Null class plays the ConcreteElement role.
  *
  */
class Visitor
{
public:
   virtual void Visit(Array& array) = 0;
   virtual void Visit(DisplayElement& string) = 0;
   virtual void Visit(Null& null) = 0;
};

/** The class ConstVisitor is an abstract base class.
  * Classes which are derived from this class should not be modifying
  * the parameters passed into the Visit functions.
  *
  * <pre>
  * Design Pattern: Visitor
  * Design Pattern Role: Visitor
  * Other Participants: 
  *    The TreeVisitor class plays the ConcreteVisitor role.
  *    The StaticTreeVisitor class plays the ConcreteVisitor role.
  *    The abstract Element class plays the Element role.
  *    The Array class plays the ConcreteElement role.
  *    The DisplayElement class plays the ConcreteElement role.
  *    The Null class plays the ConcreteElement role.
  * </pre>
  */
class ConstVisitor
{
public:
   virtual void Visit(const Array& array) = 0;
   virtual void Visit(const DisplayElement& string) = 0;
   virtual void Visit(const Null& null) = 0;
};


}