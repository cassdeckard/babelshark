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
      std::cout << "Done." << std::endl;

      // Write data to screen. (This just verifies that we read in the data correctly.)
      QuickInterpreter interpeter(elemRoot);
      const std::string& sId = interpeter["ListAvatars_Message"]["ListAvatarsMessageId"].As<String>();
      std::cout << "Message Id: " << sId << std::endl;
      const std::string& sRoom = interpeter["ListAvatars_Message"]["Room"].As<String>();
      std::cout << "Room: " << sRoom << std::endl;
/*      const std::string& sName = interpeter["ListAvatars_Message"]["AvatarsInTheRoom"][0]["Name"].As<String>();
      std::cout << "Name0: " << sName << std::endl;
      const std::string& sMale = interpeter["ListAvatars_Message"]["AvatarsInTheRoom"][0]["Male"].As<String>();
      std::cout << "Male0: " << sMale << std::endl;
      const std::string& sName1 = interpeter["ListAvatars_Message"]["AvatarsInTheRoom"][1]["Name"].As<String>();
      std::cout << "Name1: " << sName1 << std::endl;
      const std::string& sMale1 = interpeter["ListAvatars_Message"]["AvatarsInTheRoom"][1]["Male"].As<String>();
      std::cout << "Male1: " << sMale1 << std::endl;
*/
      // Write it out to a file....
      std::cout << "Writing file out...";
      Writer::Write(elemRoot, std::ofstream("AvatarsInRoomOutput.txt"));
      std::cout << "Done." << std::endl;

      // When the accept function is called, it iterates over every element in the PDI tree.
      TreeVisitor treeVisitor("root");
      elemRoot.Accept(treeVisitor);

      BabelShark::Instruction* pRootInstruction = treeVisitor.GetInstruction();

   }

   return 0;
}

