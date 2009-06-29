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

// TODO: Remove all of these
#include "AliasedInstruction.h"
#include "AsciiElement.h"
#include "UintElement.h"
#include "BoolElement.h"
#include "PadElement.h"
#include "FloatElement.h"
#include "IntElement.h"

namespace BabelShark
{
    /** The Dissector class sort of acts as our controller.
      * It is called directly from Wireshark when it receives a packet that
      * Babelshark is registered to interpret. Babelshark constructs Dissector
      * when the program starts and passes it the string name of the PDI file
      * to be read in, and an integer called _proto which is used by
      * Wireshark to identify our plugin.
      *
      * <b>Pattern roles:</b>
      * - Interpreter::Client
      * - Composite::Client
      */
	class Dissector
	{
		public:
            /** In its constructor, Dissector calls Parse() to get the root of
              * the Instruction tree. It sets _protoName to the name of the
              * root Instruction. Then it does some calls to Wireshark
              * functions to initialize the plugin.
              *
              * @param inFile
              *   the name of the PDI file to be read in
              * @param proto
              *   a handle for our protocol used to identify ourselves
              *   in calls to Wireshark code
              */
            Dissector(const char* inFile, int* proto);

            ~Dissector();

            /** ReparseTree() takes in a string for a filename, calls
              * Parse() again on it, and replaces our _RootInstruction
              * with the result to create a new Instruction tree to work with.
              * It also changes _protoName and sets a _nameChanged flag
              * so we know we need to update the display of the protocol
              * name while dissecting packets.
              *
              * @param inFile
              *   the name of the PDI file to be read in
              */
            void ReparseTree(const char* inFile);

            /** Dissect() will be called by Wireshark on every packet given
              * to it by Babelshark to dissect.
              *
              * @param tvb
              *   a struct that represents that packet data we're responsible
              *   for interpreting
              * @param pinfo
              *   contains information about the Protocol and Info
              *   columns for our packets
              * @param tree
              *   a pointer to Wireshark's protocol tree we will be modifying
              *   so Wireshark knows how to interpret our data.
              */
            void Dissect(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree);

            /** Test() is a function used purely for debugging purposes.
              * It is called by Wireshark just before Dissector is constructed.
              * What it actually does changes over the course of implementation,
              * but it is usually used to write debug output to the console.
              */
            void Test();

		private:
            /** ParseInstructions() uses all of the children of an Instruction
              * to interpret packet data and attach it to Wireshark's protocol
              * tree. After using the Instruction to interpret data, it determines
              * if it has any children and calls ParseSet() on it if so.
              *
              * NOTE: Do we need to pass in buffer if we're already passing in tvb?
              *
              * @param in
              *   the Instruction node whose children we are interpreting
              * @param tvb
              *   a struct that represents that packet data we're responsible
              *   for interpreting
              * @param tree
              *   a pointer to Wireshark's protocol tree we will be modifying
              *   so Wireshark knows how to interpret our data.
              * @param buffer
              *   data in tvb converted to char* for Instructions
              * @param offset
              *   the byte offset marking our place in the packet dissection
              */
            void ParseInstructions(Instruction* in,
                                   tvbuff_t *tvb,
                                   proto_tree *tree,
                                   char* buffer,
                                   gint &offset);

            /** ParseSet() interprets packet data of an aggregate Instruction
              * type. It creates a subtree in Wireshark's protocol tree for the
              * node, then recursively calls ParseInstructions() on the children
              * of the node, attaching them to the new subtree. This is a
              * two-part recursion as ParseSet() is itself called by
              * ParseInstructions().
              *
              * NOTE: Do we need to pass in buffer if we're already passing in tvb?
              *
              * @param in
              *   the Instruction node we are interpreting
              * @param tvb
              *   a struct that represents that packet data we're responsible
              *   for interpreting
              * @param tree
              *   a pointer to Wireshark's protocol tree we will be modifying
              *   so Wireshark knows how to interpret our data.
              * @param buffer
              *   data in tvb converted to char* for Instructions
              * @param offset
              *   the byte offset marking our place in the packet dissection
              */
            void ParseSet(Instruction* in,
                          tvbuff_t *tvb,
                          proto_tree *tree,
                          char* buffer,
                          gint &offset);

            /** _RootInstruction holds the root node of the Instruction tree
              */
            Instruction* _RootInstruction;

            /** _proto is a handle used by Wireshark to identify our protocol
              */
            int*         _proto;

            /** _ett is used by Wireshark to keep the expanded state of subtrees
              */
            gint**       _ett;

            /** _protoName contains the name of our protocol
              */
            std::string  _protoName;

            /** _nameChanged is set to true if the name of our protocol has
              * changed and needs to be updated in the Wireshark GUI
              */
            bool         _nameChanged;

            /** TODO: REMOVE **/
            AliasedInstruction* _TestAliased;
            Instruction* _TestInstruction;
	};
}

#endif //DISSECTOR_H