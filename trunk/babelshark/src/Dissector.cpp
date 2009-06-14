// $Id$

// C++ headers
#include "..\Dissector.h"

#define PROTO_NAME "Test protocol (8 byte strings)"

namespace BabelShark
{

    Dissector::Dissector(gint* ett, int proto)
        : _instruction(new AsciiElement(8, "test_ascii")),
          _instruction2(new UintElement(4, "test_uint")),
          _instruction3(new UintElement(5, "test_uint2")),
          _ett(ett),
          _proto(proto)
	{
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

        // Interpret things
        gint offset = 0;
        _instruction->Interpret(buffer + offset);  offset += _instruction->GetSizeInBytes();
        _instruction2->Interpret(buffer + offset); offset += _instruction2->GetSizeInBytes();
        _instruction3->Interpret(buffer + offset); offset += _instruction3->GetSizeInBytes();
        offset = 0;

        if (tree) { // we are being asked for details
           proto_item *ti = NULL;
           proto_tree *babelshark_tree = NULL;

           ti = proto_tree_add_item(tree, _proto, tvb, 0, -1, FALSE);

           /* proto-level text */
           std::string temp("-decoded ");
           temp += PROTO_NAME;
           proto_item_append_text(ti, temp.c_str());

           /* subtree */
           babelshark_tree = proto_item_add_subtree(ti, *_ett);
           proto_tree_add_text(babelshark_tree, tvb, offset, _instruction->GetSizeInBytes(), _instruction->Display()); offset +=_instruction->GetSizeInBytes();
           proto_tree_add_text(babelshark_tree, tvb, offset, _instruction2->GetSizeInBytes(), _instruction2->Display()); offset +=_instruction2->GetSizeInBytes();
           proto_tree_add_text(babelshark_tree, tvb, offset, _instruction3->GetSizeInBytes(), _instruction3->Display()); offset +=_instruction3->GetSizeInBytes();

       }

       // free dynamically allocated memory
       delete [] buffer;
    }

    void Dissector::Test()
    {
        //printf("Dissector::Test\n _ett: %i\n _proto: %u\n", _ett, _proto);
    }
}
