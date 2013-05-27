/*******************************************************************************

Author: Julie Betlach

Adapted from code written by: Terry Caton, tcaton(a)hotmail.com
Project Webpage: http://cajun-jsonapi.sourceforge.net/

Original code parsed files in json format.
Code now parses files in PDI format for a project for Washington University, 
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

functions: PDI_cast

PDI_cast is intended as a alternatives to static_cast and dynamic_cast. The
symantics are identical: one can cast a const/nonconst pointer/reference, and 
all conventional rules regarding casting are preserved. It is similar to 
static_cast in that it simply returns a "reinterpretation" of the pointer or
reference passed in. However, it is closer in functionality to dynamic_cast,
in that it verifies the operation is legal, and fails otherwise (returns null
during pointer cast, throws PDI::Exception during reference cast). Examples:

Number num = Number();
const Element& el = num; // implicit cast

PDI_cast<const Number&>(el); // runtime success
PDI_cast<const Array&>(el); // runtime exception

PDI_cast<Number&>(el); // compile time failure (loses const qualifier)
PDI_cast<const Number*>(el); // compile time failure (cannot convert ref to pointer)

********************************************************************************/

#pragma once


namespace PDI
{


class Element;

// reference to non-const
template <typename ElementTypeQualifiedT>
ElementTypeQualifiedT PDI_cast(Element& element);

// reference to const
template <typename ElementTypeQualifiedT>
ElementTypeQualifiedT PDI_cast(const Element& element);

// pointer to non-const
template <typename ElementTypeQualifiedT>
ElementTypeQualifiedT PDI_cast(Element* pElement);

// pointer to const
template <typename ElementTypeQualifiedT>
ElementTypeQualifiedT PDI_cast(const Element* pElement);

} // End namespace

#include "cast.inl"

