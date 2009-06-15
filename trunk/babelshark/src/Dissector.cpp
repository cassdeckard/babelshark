// $Id$

// C++ headers
#include "..\Dissector.h"
#include <sstream>

#define PDI_FILE "AvatarsInRoom.txt"

BabelShark::Instruction* Parse(std::string inFile); // delcaration; this is defined in PdiParser.cpp

namespace BabelShark
{

    Dissector::Dissector(int* proto)
        : _instruction(new AsciiElement(4, "test_ascii")),
          _instruction2(new UintElement(7, "test_uint")),
          _instruction3(new BoolElement(1, "test_bool")),
          _instruction4(new PadElement(16,  "test_padding")),
          _proto(proto)
    {
        _RootInstruction = Parse(PDI_FILE); // TODO: get this from preferences
        _protoName       = _RootInstruction->GetName();

        /* Setup protocol subtree array */
        _ett = new gint*[1]; // TODO: size array to number of InstructionSets
        *_ett[0] = -1;

        *_proto = proto_register_protocol(_protoName.c_str(),  /* name       */
                                          _protoName.c_str(),  /* short name */
                                          "babelshark");       /* abbrev     */

        proto_register_field_array(*_proto, NULL, 0);
        proto_register_subtree_array(_ett, array_length(_ett));

	}

    Dissector::~Dissector()
	{

	}

    void Dissector::Dissect(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
    {
        guint8 packet_type = tvb_get_guint8(tvb, 0);

        if (check_col(pinfo->cinfo, COL_PROTOCOL)) {
           col_set_str(pinfo->cinfo, COL_PROTOCOL, _protoName.c_str());
        }
        /* Clear out stuff in the info column */
        if (check_col(pinfo->cinfo,COL_INFO)) {
           col_clear(pinfo->cinfo,COL_INFO);
        }
        if (check_col(pinfo->cinfo, COL_INFO)) {
            col_add_fstr(pinfo->cinfo, COL_INFO, "decoded by Babelshark");
        }

        // create buffer
        int length = tvb->length;
        char* buffer = new char[length];
        const guint8* tvb_ptr = tvb_get_ptr(tvb, 0, length);
        memcpy(buffer, tvb_ptr, length);

        if (tree) { // we are being asked for details
           proto_item *ti = NULL;
           proto_tree *babelshark_tree = NULL;

           // trees
           proto_tree *sub_tree = NULL;
           proto_tree *sub_node = NULL;

           ti = proto_tree_add_item(tree, *_proto, tvb, 0, -1, FALSE);

           /* proto-level text */
           proto_item_append_text(ti, " (decoded by Babelshark)");

           // Interpret things
           gint offset = 0;
           InstructionSet* topSet;
           Instruction* currentIns;
           InstructionCollection::iterator it;

           /* subtree */
           babelshark_tree = proto_item_add_subtree(ti, *_ett[0]);
           topSet = dynamic_cast<InstructionSet*>(_RootInstruction);
           topSet->Interpret(buffer);


           // interpret children
           topSet->CreateIterator();
           it = topSet->GetIterator();
           for (int i = 0; i < 5; i++)
           {
              currentIns = *it;
              currentIns->Interpret(buffer + offset);
              proto_tree_add_text(babelshark_tree, tvb, offset, currentIns->GetSizeInBytes(), currentIns->Display());
              offset += currentIns->GetSizeInBytes();
              it++;
           }

           // subtrees
           currentIns = *it; // this now points to an InstructionSet
           InstructionSet* level1Set;
           InstructionCollection::iterator level1It;

           level1Set = dynamic_cast<InstructionSet*>(currentIns);

           for (unsigned int i = 0; i < level1Set->GetSize(); i++)
           {
               level1Set->Interpret(buffer + offset);
               std::stringstream treeDisplay;
               treeDisplay << level1Set->Display() << "[" << i << "]";
               sub_node = proto_tree_add_text(babelshark_tree, tvb, offset, level1Set->GetSizeInBytes(), treeDisplay.str().c_str());
               sub_tree = proto_item_add_subtree(sub_node, *_ett[0]);

               // interpret children
               level1Set->CreateIterator();
               level1It = level1Set->GetIterator();
               for (int j = 0; j < 2; j++)
               {
                  currentIns = *level1It;
                  currentIns->Interpret(buffer + offset);
                  proto_tree_add_text(sub_tree, tvb, offset, currentIns->GetSizeInBytes(), currentIns->Display());
                  offset += currentIns->GetSizeInBytes();
                  level1It++;
               }
           }
       }

       // free dynamically allocated memory
       delete [] buffer;
    }

    void Dissector::Test()
    {
        //printf("Dissector::Test\n _ett: %i\n _proto: %u\n", _ett[0], *_proto);
        printf("_RootInstruction:\n Name     : %s\n Size     : %u\n ByteSize : %u\n Display  : %s\n\n",
               _RootInstruction->GetName(),
               _RootInstruction->GetSize(),
               _RootInstruction->GetSizeInBytes(),
               _RootInstruction->Display());
    }
}
