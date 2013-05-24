/***********************************************

Author: Julie Betlach

Adapted from code written by: Terry Caton, tcaton(a)hotmail.com
Project Webpage: http://cajun-jsonapi.sourceforge.net/

Original code parsed files in json format.
Code now parses files in PDI format for a project for Washington University, 
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

*************************************************/

#pragma once

#include "reader.h"

#include <stdexcept>

namespace PDI
{

class Exception : public std::runtime_error
{
public:
   Exception(const std::string& sMessage) :
      std::runtime_error(sMessage) {}
};



class ScanException : public Exception
{
public:
   ScanException(const std::string& sMessage, const Reader::Location& locError) :
      Exception(sMessage),
      m_locError(locError) {}

   Reader::Location m_locError;
};

class ParseException : public Exception
{
public:
   ParseException(const std::string& sMessage, const Reader::Location& locTokenBegin, const Reader::Location& locTokenEnd) :
      Exception(sMessage),
      m_locTokenBegin(locTokenBegin),
      m_locTokenEnd(locTokenEnd) {}

   Reader::Location m_locTokenBegin;
   Reader::Location m_locTokenEnd;
};

} // End namespace
