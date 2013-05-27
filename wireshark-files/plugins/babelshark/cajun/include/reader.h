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

/** The Reader class is used to read in a file in PDI Format.
* The overall design of this class remains consitent with the code from SourceForge.
* However, changes have been made to read in the new format.
*
* <pre>
* Design Pattern: None
* Design Pattern Role: None
* </pre>
*
* This class provides a public function named Read.
* There are two primary steps which occur in the Read function.
* First, the file is scanned for tokens and a token stream is created.
* Second, the token stream is parsed.
*
* While the token stream is being parsed, one of three actions will occur:
* 1) If a statictype is being parsed, then a StaticTypeDeclarationElement will be added to the StaticTypeDeclarationCollection.
* 2) If a dynamictype is being parsed, then a DynamicTypeDeclarationElement will be added to the DynamicTypeDeclarationCollection.
* 1) If a message is being parsed, then a PDI Tree will be created using the elementRoot passed into the Read function.
*
***/
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

   enum TokenType
   {
      TOKEN_ARRAY_BEGIN,         //    [
      TOKEN_ARRAY_END,           //    ]
      TOKEN_DYNAMICTYPE_BEGIN,   //    {
      TOKEN_DYNAMICTYPE_END,     //    }
      TOKEN_DYNAMICTYPE,         //    dynamictype
      TOKEN_STATICTYPE,          //    statictype
      TOKEN_NEXT_ELEMENT,  //    ,
      TOKEN_MEMBER_ASSIGN, //    :
      TOKEN_STRING,        //    "xxx"
      TOKEN_NUMBER,        //    000
      TOKEN_NULL,          //    null
      TOKEN_COMMENT        //    // ......
   };

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
