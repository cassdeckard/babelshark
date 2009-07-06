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

class Reader
{
public:
   struct Location
   {
      Location();

      /** document line, zero-indexed
        ***/
      unsigned int m_nLine;

      /** character offset from beginning of line, zero indexed
        ***/
      unsigned int m_nLineOffset;

      /** character offset from entire document, zero indexed
        ***/
      unsigned int m_nDocOffset;
   };

   static void Read(Element& elementRoot, std::istream& istr);

private:
   class InputStream;

   enum TokenType;
   struct Token;
   typedef std::vector<Token> Tokens;
   class TokenStream;

   /** scanning istream into token sequence
     ***/
   void Scan(Tokens& tokens, InputStream& inputStream);

   void EatWhiteSpace(InputStream& inputStream);
   void MatchComment(std::string& sComment, InputStream& inputStream);
   void MatchString(std::string& sValue, InputStream& inputStream);
   void MatchNumber(std::string& sNumber, InputStream& inputStream);
   void MatchExpectedString(const std::string& sExpected, InputStream& inputStream);

   /** parsing token sequence into element structure
     ***/
   void Parse(Element& element, TokenStream& tokenStream);
   void Parse(Array& array, TokenStream& tokenStream);
   void ParseDynamicTypeDeclaration(const std::string& sName, Reader::TokenStream& tokenStream);
   void ParseStaticTypeDeclaration(const std::string& sName, Reader::TokenStream& tokenStream);
   void Parse(DisplayElement& string, TokenStream& tokenStream);
   void Parse(Null& null, TokenStream& tokenStream);

   const std::string& MatchExpectedToken(TokenType nExpected, TokenStream& tokenStream);
};


} // End namespace