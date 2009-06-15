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