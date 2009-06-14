// PdiParser.cpp : Defines the entry point for the console application.
//                 (based on main.cpp)
//
// $Id$
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

BabelShark::Instruction* Parse()
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
      std::cout << "Done." << std::endl;

      // Write data to screen. (This just verifies that we read in the data correctly.)
      QuickInterpreter interpeter(elemRoot);

      // Write it out to a file....
      std::cout << "Writing file out...";
      Writer::Write(elemRoot, std::ofstream("AvatarsInRoomOutput.txt"));
      std::cout << "Done." << std::endl;

      // When the accept function is called, it iterates over every element in the PDI tree.
      TreeVisitor treeVisitor("root");
      elemRoot.Accept(treeVisitor);

      BabelShark::Instruction* pRootInstruction = treeVisitor.GetInstruction();
      return pRootInstruction;

   }

}

