// $Id$

// C++ headers
#include "..\Dissector.h"

#define PROTO_NAME "Test protocol (8 byte strings)"

BabelShark::Instruction* Parse(); // delcaration; this is defined in PdiParser.cpp

namespace BabelShark
{

    Dissector::Dissector(gint* ett, int proto)
        : _instruction(new AsciiElement(4, "test_ascii")),
          _instruction2(new UintElement(7, "test_uint")),
          _instruction3(new BoolElement(1, "test_bool")),
          _instruction4(new PadElement(16,  "test_padding")),
          _ett(ett),
          _proto(proto)
    {
        _RootInstruction = Parse();
	}

    Dissector::~Dissector()
	{

	}

    void Dissector::Dissect(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
    {
        guint8 packet_type = tvb_get_guint8(tvb, 0);

        if (check_col(pinfo->cinfo, COL_PROTOCOL)) {
           col_set_str(pinfo->cinfo, COL_PROTOCOL, PROTO_NAME);
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
           proto_tree *root_tree = NULL;
           proto_tree *root_node = NULL;
           proto_tree *sub_tree = NULL;
           proto_tree *sub_node = NULL;

           ti = proto_tree_add_item(tree, _proto, tvb, 0, -1, FALSE);

           /* proto-level text */
           std::string decoded("-decoded ");
           decoded += PROTO_NAME;
           proto_item_append_text(ti, decoded.c_str());

           // Interpret things
           gint offset = 0;
           InstructionSet* tempSet;
           Instruction* tempIns;
           InstructionCollection::iterator it;

           /* subtree */
           babelshark_tree = proto_item_add_subtree(ti, *_ett);
           tempSet = dynamic_cast<InstructionSet*>(_RootInstruction->GetChild());
           tempSet->Interpret(buffer);
           root_node = proto_tree_add_text(babelshark_tree, tvb, offset, tempSet->GetSizeInBytes(), tempSet->Display());
           root_tree = proto_item_add_subtree(root_node, *_ett);


           // interpret children
           tempSet->CreateIterator();
           it = tempSet->GetIterator();
           for (int i = 0; i < 5; i++)
           {
              tempIns = *it;
              tempIns->Interpret(buffer + offset);
              proto_tree_add_text(root_tree, tvb, offset, tempIns->GetSizeInBytes(), tempIns->Display());
              offset += tempIns->GetSizeInBytes();
              it++;
           }

           // subtrees
           tempIns = *it; // this now points to an InstructionSet
           tempSet = dynamic_cast<InstructionSet*>(tempIns);
           tempSet->Interpret(buffer + offset);
           sub_node = proto_tree_add_text(root_tree, tvb, offset, tempSet->GetSizeInBytes(), tempSet->Display());
           sub_tree = proto_item_add_subtree(sub_node, *_ett);

           // interpret children
           tempSet->CreateIterator();
           it = tempSet->GetIterator();
           for (int j = 0; j < 2; j++)
           {
              tempIns = *it;
              tempIns->Interpret(buffer + offset);
              proto_tree_add_text(sub_tree, tvb, offset, tempIns->GetSizeInBytes(), tempIns->Display());
              offset += tempIns->GetSizeInBytes();
              it++;
           }

       }

       // free dynamically allocated memory
       delete [] buffer;
    }

    void Dissector::Test()
    {
        //printf("Dissector::Test\n _ett: %i\n _proto: %u\n", _ett, _proto);
        printf("_RootInstruction:\n Name     : %s\n Size     : %u\n ByteSize : %u\n Display  : %s\n\n",
               _RootInstruction->GetName(),
               _RootInstruction->GetSize(),
               _RootInstruction->GetSizeInBytes(),
               _RootInstruction->Display());
    }
}
