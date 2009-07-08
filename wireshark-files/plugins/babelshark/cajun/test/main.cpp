/**********************************************

Author: Julie Betlach

Adapted from code written by: Terry Caton, tcaton(a)hotmail.com
Project Webpage: http://cajun-jsonapi.sourceforge.net/

Original code parsed files in json format.
Code now parses files in PDI format for a project for Washington University, 
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

***********************************************/

#include "elements.h"
#include "reader.h"
#include "cast.h"
#include "exception.h"

#include "TreeVisitor.h"
#include "BabelSharkSupport.h"

#include <iostream>
#include <fstream>


/** The Main() function in the Main.cpp file is used to test the
  * PDI Parser functionality.  This allows us to perform subsystem
  * testing on the parser without needing the Dissector or Wireshark code.
  */
int main()
{
   using namespace PDI;

   {
      // Read a file in PDI Format.
      std::cout << "Read the BabelShark.pdi file..." << std::endl;
      Element elemRoot = DisplayElement();
      Reader::Read(elemRoot, std::ifstream("BabelShark.pdi"));
      std::cout << "Done." << std::endl << std::endl;

      // Fill the data dictionary with statictypes and dynamictypes
      // and create the instruction tree.
      std::cout << "Fill the Data Dictionary and Create the Instruction Tree..." << std::endl;
      CreateInstructionTreeAndFillDataDictionary(elemRoot, true);
      std::cout << "Done." << std::endl << std::endl;
   }

   return 0;
}

