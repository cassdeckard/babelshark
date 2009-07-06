/**********************************************

Author: Julie Betlach

Adapted from code written by: Terry Caton, tcaton(a)hotmail.com
Project Webpage: http://cajun-jsonapi.sourceforge.net/

Original code parsed files in json format.
Code now parses files in PDI format for a project for Washington University, 
course CSE 533S: Pattern Oriented Software Design and Development, Summer 2009.

***********************************************/

#include "elements.h"
#include "quick.h"
#include "writer.h"
#include "reader.h"
#include "cast.h"
#include "exception.h"

#include "TreeVisitor.h"
#include "BabelSharkSupport.h"

// These are just included in Main so that we can use reverse engineering
// to get the class diagram.
#include "DynamicTypeDeclarationElement.h"
#include "DynamicTypeDeclarationCollection.h"


#include <iostream>
#include <fstream>



int main()
{
   using namespace PDI;

   {
      // AvatarsInRoom example
      // Currently this file is still in a JSON like format.
      // It will eventually be changed to the PDI format.
      // That will be done after we get the TreeVisitor to create an instruction tree.
      // Some items may be hard-coded so instruction tree creation can be completed (for example size).
      std::cout << "Read the AvatarInRoom.txt file..." << std::endl;
      Element elemRoot = DisplayElement();
      Reader::Read(elemRoot, std::ifstream("AvatarsInRoom.txt"));
      std::cout << "Done." << std::endl << std::endl;

      // Write data to screen. (This just verifies that we read in the data correctly.)
/*      std::cout << "Testing the QuickInterpreter..." << std::endl;
      QuickInterpreter interpeter(elemRoot);
      const std::string& sId = interpeter["ListAvatarsMessageId"].As<DisplayElement>();
      std::cout << "Message Id: " << sId << std::endl;
      const std::string& sRoom = interpeter["Room"].As<DisplayElement>();
      std::cout << "Room: " << sRoom << std::endl;
      const std::string& sName = interpeter["AvatarsInTheRoom"]["Name"].As<DisplayElement>();
      std::cout << "Name: " << sName << std::endl;
      const std::string& sMale = interpeter["AvatarsInTheRoom"]["Male"].As<DisplayElement>();
      std::cout << "Male: " << sMale << std::endl;
      std::cout << "Done." << std::endl << std::endl;
*/
      // Write it out to a file....
      std::cout << "Writing file out..." << std::endl;
      Writer::Write(elemRoot, std::ofstream("AvatarsInRoomOutput.txt"));
      std::cout << "Done." << std::endl << std::endl;

/*      // When the accept function is called, it iterates over every element in the PDI tree.
      std::cout << "Testing TreeVisitor..." << std::endl;
      // Pass the second arguement as true, to see output statements written to the screen for unit testing purposes.
      TreeVisitor treeVisitor(elemRoot.Name(), true);
 
      // Don't include the second arguement (or pass false) to prevent statements from being written to the screen.
//      TreeVisitor treeVisitor(elemRoot.Name());
      elemRoot.Accept(treeVisitor);
      std::cout << "Done." << std::endl << std::endl;
*/

      // Try out the new function for Phase 2 testing.
      CreateInstructionTreeAndFillDataDictionary(elemRoot, true);
   }

   return 0;
}

