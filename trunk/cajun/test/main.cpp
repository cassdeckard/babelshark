// PDI.cpp : Defines the entry point for the console application.
//
// Modifications for Wireshark Dissector Project: Julie Betlach, julie.betlach(a)gmail.com

#include "elements.h"
#include "quick.h"
#include "writer.h"
#include "reader.h"
#include "cast.h"
#include "exception.h"
#include "TreeVisitor.h"

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
      Element elemRoot = String();
      Reader::Read(elemRoot, std::ifstream("AvatarsInRoom.txt"));
      std::cout << "Done." << std::endl << std::endl;

      // Write data to screen. (This just verifies that we read in the data correctly.)
      std::cout << "Testing the QuickInterpreter..." << std::endl;
      QuickInterpreter interpeter(elemRoot);
      const std::string& sId = interpeter["ListAvatarsMessageId"].As<String>();
      std::cout << "Message Id: " << sId << std::endl;
      const std::string& sRoom = interpeter["Room"].As<String>();
      std::cout << "Room: " << sRoom << std::endl;
      const std::string& sName = interpeter["AvatarsInTheRoom"]["Name"].As<String>();
      std::cout << "Name: " << sName << std::endl;
      const std::string& sMale = interpeter["AvatarsInTheRoom"]["Male"].As<String>();
      std::cout << "Male: " << sMale << std::endl;
      std::cout << "Done." << std::endl << std::endl;

      // Write it out to a file....
      std::cout << "Writing file out..." << std::endl;
      Writer::Write(elemRoot, std::ofstream("AvatarsInRoomOutput.txt"));
      std::cout << "Done." << std::endl << std::endl;

      // When the accept function is called, it iterates over every element in the PDI tree.
      std::cout << "Testing TreeVisitor..." << std::endl;
      // Pass the second arguement as true, to see output statements written to the screen for unit testing purposes.
//      TreeVisitor treeVisitor(elemRoot.Name(), true);
 
      // Don't include the second arguement (or pass false) to prevent statements from being written to the screen.
      TreeVisitor treeVisitor(elemRoot.Name());
      elemRoot.Accept(treeVisitor);
      std::cout << "Done." << std::endl << std::endl;

      BabelShark::Instruction* pRootInstruction = treeVisitor.GetInstruction();

   }

   return 0;
}

