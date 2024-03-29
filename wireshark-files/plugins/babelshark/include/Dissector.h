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
#include <epan/expert.h>
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
            /** DissectInstructions() uses all of the children of an Instruction
              * to interpret packet data and attach it to Wireshark's protocol
              * tree. After using the Instruction to interpret data, it determines
              * if it has any children and calls DissectSet() on it if so.
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
            void DissectInstructions(Instruction* in,
                                   tvbuff_t *tvb,
                                   proto_tree *tree,
                                   char* buffer,
                                   gint &offset);

            /** DissectSet() interprets packet data of an aggregate Instruction
              * type. It creates a subtree in Wireshark's protocol tree for the
              * node, then recursively calls DissectInstructions() on the children
              * of the node, attaching them to the new subtree. This is a
              * two-part recursion as DissectSet() is itself called by
              * DissectInstructions().
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
            void DissectSet(Instruction* in,
                          tvbuff_t *tvb,
                          proto_tree *tree,
                          char* buffer,
                          gint &offset);


            /** ShiftBits() takes the current packet buffer and shifts it by the
              * number of bits specified in offset, then returns a shifted buffer of
              * the specified size in bytes. It is used to feed Instructions that
              * need to start reading from the middle of a byte in the buffer, because
              * a previous Instruction did not Interpret the entire byte.
              *
              * @param buffer
              *   the input buffer
              * @param size
              *   number of bytes to return
              * @param offset
              *   number of bits to shift
              */
            char* ShiftBits(char* buffer, unsigned int size, unsigned int offset);

            /** ParsePDI() makes the calls to the PDI Parser subsystem to read in
              * the file supplied by the plugin and construct the _RootInstruction
              * tree from it.
              *
              * ParsePDI() also performs exception handling. If it encounters
              * any exceptions thrown from PDI Parser it creates a single Instruction
              * of zero Size whose Name is whatever information was passed in the
              * exception. The Dissector will recognize this as represnting an error
              * and pass the message to Wireshark's error handling system rather than
              * attempt to use the Instruction to dissect.
              *
              * @param inFile
              *   the name of the file to read in
              */
            Instruction* ParsePDI(std::string inFile);

            /** _RootInstruction holds the root node of the Instruction tree
              */
            Instruction* _RootInstruction;

            /** _proto is a handle used by Wireshark to identify our protocol
              */
            int*         _proto;

            /** _protoName contains the name of our protocol
              */
            std::string  _protoName;

            /** _nameChanged is set to true if the name of our protocol has
              * changed and needs to be updated in the Wireshark GUI
              */
            bool         _nameChanged;

            /** _nameChanged is set to true if the name of our protocol has
              * changed and needs to be updated in the Wireshark GUI
              */
            unsigned int _bitOffset;

            /** TODO: REMOVE **/
            AliasedInstruction* _TestAliased;
            /** TODO: REMOVE **/
            Instruction* _TestInstruction;
	};
}

#endif //DISSECTOR_H
