/***********************************************

Author: Julie Betlach

Adapted from code written by: Terry Caton, tcaton(a)hotmail.com
Project Webpage: http://cajun-jsonapi.sourceforge.net/

Original code parsed files in json format.
Code now parses files in PDI format for a project for Washington University, 
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

*************************************************/

#include "reader.h"
#include "exception.h"
#include "cast.h"
#include <cassert>
#include <set>
#include <sstream>

#include "DynamicTypeElement.h"
#include "DynamicTypeCollection.h"
#include "StaticTypeDeclarationElement.h"
#include "StaticTypeDeclarationCollection.h"


/*  

TODO:
* better documentation
* unicode character decoding

***/

namespace PDI
{


Reader::Location::Location() :
   m_nLine(0),
   m_nLineOffset(0),
   m_nDocOffset(0)
{}

enum Reader::TokenType
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


//////////////////////
// Reader::InputStream

class Reader::InputStream // would be cool if we could inherit from std::istream & override "get"
{
public:
   InputStream(std::istream& iStr) :
      m_iStr(iStr) {}

   // protect access to the input stream, so we can keeep track of document/line offsets
   std::istream::int_type Get(); // big, define outside
   std::istream::int_type Peek() {
      assert(m_iStr.eof() == false); // enforce reading of only valid stream data 
      return m_iStr.peek();
   }

   bool EOS() {
      m_iStr.peek(); // apparently eof flag isn't set until a character read is attempted. whatever.
      return m_iStr.eof();
   }

   const Location& GetLocation() const { return m_Location; }

private:
   std::istream& m_iStr;
   Location m_Location;
};


std::istream::int_type Reader::InputStream::Get()
{
   assert(m_iStr.eof() == false); // enforce reading of only valid stream data 
   std::istream::int_type nChar = m_iStr.get();
   
   ++m_Location.m_nDocOffset;
   if (nChar == '\n')
   {
      ++m_Location.m_nLine;
      m_Location.m_nLineOffset = 0;
   }
   else
   {
      ++m_Location.m_nLineOffset;
   }

   return nChar;
}



////////////////
// Reader::Token

struct Reader::Token
{
   TokenType nType;
   std::string sValue;

   // for malformed file debugging
   Reader::Location locBegin;
   Reader::Location locEnd;
};
   


//////////////////////
// Reader::TokenStream

class Reader::TokenStream
{
public:
   TokenStream(const Tokens& tokens);

   const Token& Peek();
   const Token& Get();

   bool EOS() const;

private:
   const Tokens& m_Tokens;
   Tokens::const_iterator m_itCurrent;
};


Reader::TokenStream::TokenStream(const Tokens& tokens) :
   m_Tokens(tokens),
   m_itCurrent(tokens.begin())
{}

const Reader::Token& Reader::TokenStream::Peek() {
   assert(m_itCurrent != m_Tokens.end());
   return *(m_itCurrent); 
}

const Reader::Token& Reader::TokenStream::Get() {
   assert(m_itCurrent != m_Tokens.end());
   return *(m_itCurrent++); 
}

bool Reader::TokenStream::EOS() const {
   return m_itCurrent == m_Tokens.end(); 
}

///////////////////
// Reader (finally)

void Reader::Read(Element& elementRoot, std::istream& istr)
{
   Reader reader;

   Tokens tokens;
   InputStream inputStream(istr);
   reader.Scan(tokens, inputStream);

   TokenStream tokenStream(tokens);
   // Needed to add looping here, because we now have multiple top-level items in the file.
   // Before we just had one top-level message.  Now we have that, plus dynamictypes and statictypes.
   while (tokenStream.EOS() == false)
   {
      reader.Parse(elementRoot, tokenStream);
   }

   if (tokenStream.EOS() == false)
   {
      const Token& token = tokenStream.Peek();
      std::string sMessage = "Expected End of token stream; found " + token.sValue;
      throw ParseException(sMessage, token.locBegin, token.locEnd);
   }
}


void Reader::Scan(Tokens& tokens, InputStream& inputStream)
{
   while (EatWhiteSpace(inputStream), // ignore any leading white space...
          inputStream.EOS() == false) // ...before checking for EOS
   {
      // if all goes well, we'll create a token each pass
      Token token;
      token.locBegin = inputStream.GetLocation();

      // gives us null-terminated string
      char sChar[2] = {0};
      sChar[0] = inputStream.Peek();

      switch (sChar[0])
      {
         case '[':
            MatchExpectedString(sChar, inputStream);
            token.nType = TOKEN_ARRAY_BEGIN;
            break;

         case ']':
            MatchExpectedString(sChar, inputStream);
            token.nType = TOKEN_ARRAY_END;
            break;

         case '{':
            MatchExpectedString(sChar, inputStream);
            token.nType = TOKEN_DYNAMICTYPE_BEGIN;
            break;

         case '}':
            MatchExpectedString(sChar, inputStream);
            token.nType = TOKEN_DYNAMICTYPE_END;
            break;

         case ',':
            MatchExpectedString(sChar, inputStream);
            token.nType = TOKEN_NEXT_ELEMENT;
            break;

         case '/':
            MatchComment(token.sValue, inputStream);
            token.nType = TOKEN_COMMENT;
            break;

         case ':':
            MatchExpectedString(sChar, inputStream);
            token.nType = TOKEN_MEMBER_ASSIGN;
            break;

         case '"':
            MatchString(token.sValue, inputStream);
            token.nType = TOKEN_STRING;
            break;

         case '-':
         case '0':
         case '1':
         case '2':
         case '3':
         case '4':
         case '5':
         case '6':
         case '7':
         case '8':
         case '9':
            MatchNumber(token.sValue, inputStream);
            token.nType = TOKEN_NUMBER;
            break;

         case 'n':
            token.sValue = "null";
            MatchExpectedString(token.sValue, inputStream);
            token.nType = TOKEN_NULL;
            break;

         case 'd':
            token.sValue = "dynamictype";
            MatchExpectedString(token.sValue, inputStream);
            token.nType = TOKEN_DYNAMICTYPE;
            break;

         case 's':
            token.sValue = "statictype";
            MatchExpectedString(token.sValue, inputStream);
            token.nType = TOKEN_STATICTYPE;
            break;

         default:
         {
            std::string sErrorMessage = "Unexpected character in stream: " + sChar[0];
            throw ScanException(sErrorMessage, inputStream.GetLocation());
         }
      }

      token.locEnd = inputStream.GetLocation();
      tokens.push_back(token);
   }
}


void Reader::EatWhiteSpace(InputStream& inputStream)
{
   while (inputStream.EOS() == false && 
          ::isspace(inputStream.Peek()))
      inputStream.Get();
}

void Reader::MatchExpectedString(const std::string& sExpected, InputStream& inputStream)
{
   std::string::const_iterator it(sExpected.begin()),
                               itEnd(sExpected.end());
   for ( ; it != itEnd; ++it)
   {
      if (inputStream.EOS() ||      // did we reach the end before finding what we're looking for...
          inputStream.Get() != *it) // ...or did we find something different?
      {
         std::string sMessage = "Expected string: " + sExpected;
         throw ScanException(sMessage, inputStream.GetLocation());
      }
   }

   // all's well if we made it here, return quietly
}


void Reader::MatchComment(std::string& sComment, InputStream& inputStream)
{
   MatchExpectedString("//", inputStream);

   while (inputStream.EOS() == false &&
          inputStream.Peek() != '\n')
   {
      sComment.push_back(inputStream.Get());
   }
}


void Reader::MatchString(std::string& string, InputStream& inputStream)
{
   MatchExpectedString("\"", inputStream);
   
   while (inputStream.EOS() == false &&
          inputStream.Peek() != '"')
   {
      char c = inputStream.Get();

      // escape?
      if (c == '\\' &&
          inputStream.EOS() == false) // shouldn't have reached the end yet
      {
         c = inputStream.Get();
         switch (c)
         {
            case '/':      string.push_back('/');     break;
            case '"':      string.push_back('"');     break;
            case '\\':     string.push_back('\\');    break;
            case 'b':      string.push_back('\b');    break;
            case 'f':      string.push_back('\f');    break;
            case 'n':      string.push_back('\n');    break;
            case 'r':      string.push_back('\r');    break;
            case 't':      string.push_back('\t');    break;
            case 'u':      // TODO: what do we do with this?
            default:
            {
               std::string sMessage = "Unrecognized escape sequence found in string: \\" + c;
               throw ScanException(sMessage, inputStream.GetLocation());
            }
         }
      }
      else
      {
         string.push_back(c);
      }
   }

   // eat the last '"' that we just peeked
   MatchExpectedString("\"", inputStream);
}


void Reader::MatchNumber(std::string& sNumber, InputStream& inputStream)
{
   const char sNumericChars[] = "0123456789";
   std::set<char> numericChars;
   numericChars.insert(sNumericChars, sNumericChars + sizeof(sNumericChars));

   while (inputStream.EOS() == false &&
          numericChars.find(inputStream.Peek()) != numericChars.end())
   {
      sNumber.push_back(inputStream.Get());   
   }
}


void Reader::Parse(Element& element, Reader::TokenStream& tokenStream)
{
   if (tokenStream.EOS())
   {
      std::string sMessage = "Unexpected end of token stream";
      throw ParseException(sMessage, Location(), Location()); // nowhere to point to
   }

   std::string sName;
   Token token = tokenStream.Peek();

   if (token.nType == TOKEN_DYNAMICTYPE)
   {
      // If the first token is dynamictype, then assume we are parsing a dynamictype.
      MatchExpectedToken(TOKEN_DYNAMICTYPE, tokenStream);
      sName = MatchExpectedToken(TOKEN_STRING, tokenStream);
      ParseDynamicTypeDeclaration(sName, tokenStream);
      token = tokenStream.Peek();
   }
   else if (token.nType == TOKEN_STATICTYPE)
   {
      // If the first token is statictype, then assume we are parsing a statictype.
      MatchExpectedToken(TOKEN_STATICTYPE, tokenStream);
      sName = MatchExpectedToken(TOKEN_STRING, tokenStream);
      ParseStaticTypeDeclaration(sName, tokenStream);
      token = tokenStream.Peek();
   }
   else if (token.nType == TOKEN_COMMENT)
   {
      MatchExpectedToken(TOKEN_COMMENT, tokenStream);
   }
   else
   {
      // If the first token is a string, then assume we are parsing a message root.
      sName = MatchExpectedToken(TOKEN_STRING, tokenStream);
      MatchExpectedToken(TOKEN_MEMBER_ASSIGN, tokenStream);
      token = tokenStream.Peek();

      switch (token.nType)
      {
         case TOKEN_ARRAY_BEGIN:
            element = Array();
            Parse(PDI_cast<Array&>(element), tokenStream);
            break;

         case TOKEN_STRING:
            element = DisplayElement();
            Parse(PDI_cast<DisplayElement&>(element), tokenStream);
            break;

         case TOKEN_NULL:
            element = Null();
            Parse(PDI_cast<Null&>(element), tokenStream);
            break;

         case TOKEN_COMMENT:
            // do nothing.
            break;

         default:
         {
            std::string sMessage = "Unexpected token: " + token.sValue;
            throw ParseException(sMessage, token.locBegin, token.locEnd);
         }
      }
   }

   element.SetName(sName);
}


void Reader::Parse(Array& array, Reader::TokenStream& tokenStream)
{
   MatchExpectedToken(TOKEN_ARRAY_BEGIN, tokenStream);

   bool bContinue = (tokenStream.EOS() == false &&
                     tokenStream.Peek().nType != TOKEN_ARRAY_END);
   while (bContinue)
   {
      Element element;

      Parse(element, tokenStream);

      // try adding it to the array (this could throw)
      array.Insert(element);

      bContinue = (tokenStream.EOS() == false &&
                   tokenStream.Peek().nType == TOKEN_NEXT_ELEMENT);
      if (bContinue)
         MatchExpectedToken(TOKEN_NEXT_ELEMENT, tokenStream);
   }

   MatchExpectedToken(TOKEN_ARRAY_END, tokenStream);

   // Finally, look for the dimension of this array.
   // We are now looking for a string (instead of a number) so we can support variable length arrays.
   std::string sNumber = MatchExpectedToken(TOKEN_STRING, tokenStream);

   array.SetDimension(sNumber);
}


void Reader::ParseDynamicTypeDeclaration(const std::string& sName, Reader::TokenStream& tokenStream)
{
   DynamicTypeElement element;
   element.SetName(sName);

   MatchExpectedToken(TOKEN_DYNAMICTYPE_BEGIN, tokenStream);

   DynamicTypeEntry dynTypeEntry;

   bool bContinue = (tokenStream.EOS() == false &&
                     tokenStream.Peek().nType != TOKEN_DYNAMICTYPE_END);
   while (bContinue)
   {
      std::string string = MatchExpectedToken(TOKEN_STRING, tokenStream);
      std::istringstream ss(string);
      ss >> dynTypeEntry.first >> dynTypeEntry.second;

      element.Insert(dynTypeEntry);

      bContinue = (tokenStream.EOS() == false &&
                   tokenStream.Peek().nType == TOKEN_NEXT_ELEMENT);
      if (bContinue)
         MatchExpectedToken(TOKEN_NEXT_ELEMENT, tokenStream);
   }

   DynamicTypeCollection::Instance().Insert(element);
   MatchExpectedToken(TOKEN_DYNAMICTYPE_END, tokenStream);

}


void Reader::ParseStaticTypeDeclaration(const std::string& sName, Reader::TokenStream& tokenStream)
{
   // Create a StaticTypeDelcaration element.
   StaticTypeDeclaration staticTypeElement(sName, 1);

   //Parse(PDI_cast<Array&>(element), tokenStream);
   // (here we are only dealing with the part starting with the first [
   // and ending with the number at the end after the last ]).
   // At this point we have already read in "statictype" and the name of the type (ie "&HEADER").
   Parse((Array&)(staticTypeElement), tokenStream);
   
   StaticTypeDeclarationCollection::Instance().Insert(staticTypeElement);

}


void Reader::Parse(DisplayElement& string, Reader::TokenStream& tokenStream)
{
   string = MatchExpectedToken(TOKEN_STRING, tokenStream);
}


void Reader::Parse(Null& null, Reader::TokenStream& tokenStream)
{
   MatchExpectedToken(TOKEN_NULL, tokenStream);
}


const std::string& Reader::MatchExpectedToken(TokenType nExpected, Reader::TokenStream& tokenStream)
{
   if (tokenStream.EOS())
   {
      std::string sMessage = "Unexpected End of token stream";
      throw ParseException(sMessage, Location(), Location()); // nowhere to point to
   }

   const Token& token = tokenStream.Get();
   if (token.nType != nExpected)
   {
      std::string sMessage = "Unexpected token: " + token.sValue;
      throw ParseException(sMessage, token.locBegin, token.locEnd);
   }

   return token.sValue;
}

} // End namespace
