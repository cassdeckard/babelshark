// $Id$

#ifndef DISSECTOR_H
#define DISSECTOR_H

// C headers
extern "C" {

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <epan/packet.h>
#include <epan/prefs.h>
}

// C++ headers
#include "Instruction.h"
#include "InstructionSet.h"
//#include "Iterator.h"

/*
	Design Pattern Used: Chain of Responsibility
	Class: Dissector
	Handles Dissection of a packet at a level lower than TCP/UDP.
	Calls on the Cajun Parser that reads in an input file.
	Calls on Instruction objects to Interpret() a packet.
*/


namespace BabelShark
{
	class Dissector
	{
		public:
            Dissector(const char* inFile, int* proto);
            ~Dissector();

            void Dissect(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree);
            void Test();

            void ReparseTree(const char* inFile);

		private:
            Instruction* _RootInstruction;
            int*         _proto;
            gint**       _ett;
            std::string  _protoName;
            bool         _nameChanged;
	};
}

#endif //DISSECTOR_H