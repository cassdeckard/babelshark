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

BabelShark::Instruction* Parse(std::string inFile)
{
   using namespace PDI;

   {
       /*
      // First things first! Check to make sure we didn't get a null pointer
      if (&inFile == NULL)
      {
          // Those bastards...
          return new BabelShark::Instruction(0, "ERR_NULL_FILENAME");
      }*/

      // First things first! Check to make sure the file exists. If it doesn't, erupt into a frenzied rage!
      std::ifstream fin(inFile.c_str());
      if (fin.fail())
      {
          return new BabelShark::Instruction(0, "ERR_FILE_NOT_FOUND");
      }

      std::cout << "Read the AvatarInRoom.txt file..." << std::endl;
      Element elemRoot = DisplayElement();
      Reader::Read(elemRoot, fin);
      std::cout << "Done." << std::endl;

      // Write data to screen. (This just verifies that we read in the data correctly.)
      QuickInterpreter interpeter(elemRoot);

      // Write it out to a file....
      std::cout << "Writing file out...";
      std::string outFile(inFile + "_out");
      Writer::Write(elemRoot, std::ofstream(outFile.c_str()));
      std::cout << "Done." << std::endl;

      // When the accept function is called, it iterates over every element in the PDI tree.
      TreeVisitor treeVisitor(elemRoot.Name());
      elemRoot.Accept(treeVisitor);

      BabelShark::Instruction* pRootInstruction = treeVisitor.GetInstruction();
      return pRootInstruction;

   }

}

