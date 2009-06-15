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
#include "InstructionSet.h"  //note: won't need later
#include "AsciiElement.h" //note: won't need later
#include "UintElement.h"  //note: won't need later
#include "BoolElement.h"  //note: won't need later
#include "PadElement.h"  //note: won't need later

namespace BabelShark
{
	class Dissector
	{
		public:
            Dissector(int* proto);
            ~Dissector();

            void Dissect(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree);
            void Test();

		private:
            Instruction* _RootInstruction;
            Instruction* _instruction;
            Instruction* _instruction2;
            Instruction* _instruction3;
            Instruction* _instruction4;
            int*         _proto;
            gint**       _ett;
            std::string  _protoName;
	};
}

#endif //DISSECTOR_H