/* packet-babelshark.c
 * Routines for babelshark dissection
 *
 * $Id$
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <epan/packet.h>
#include "packet-babelshark.h"

static int proto_babelshark = -1;
static int hf_babelshark_pdu = -1;

static gint ett_babelshark = -1;

static const value_string babelshark_vals[] = {
   { 0,   "ZERO" },
   { 1,   "ONE" },
   { 0,    NULL }
};

static void
dissect_babelshark(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
   if (check_col(pinfo->cinfo, COL_PROTOCOL)) {
      col_set_str(pinfo->cinfo, COL_PROTOCOL, "BABELSHARK");
   }
   /* Clear out stuff in the info column */
   if (check_col(pinfo->cinfo,COL_INFO)) {
      col_clear(pinfo->cinfo,COL_INFO);
   }
   
   if (tree) { /* we are being asked for details */
      proto_item *ti = NULL;
      proto_tree *babelshark_tree = NULL;

      ti = proto_tree_add_item(tree, proto_babelshark, tvb, 0, -1, FALSE);
      babelshark_tree = proto_item_add_subtree(ti, ett_babelshark);
      proto_tree_add_item(babelshark_tree, hf_babelshark_pdu, tvb, 0, 1, FALSE);
   }

}

void
proto_register_babelshark(void)
{
   static hf_register_info hf[] = {
      { &hf_babelshark_pdu, 
         {"Babelshark defined PDU", 
          "babelshark.pdu", 
          FT_UINT32, BASE_DEC,
          VALS(babelshark_vals), 0, 
          "Babelshark PDU", HFILL 
         }
      }
   };
   
   /* Setup protocol subtree array */
   static gint *ett[] = {
      &ett_babelshark
   };

   proto_babelshark = proto_register_protocol("Babelshark",  /* name       */
                                              "BABELSHARK",  /* short name */
                                              "babelshark"); /* abbrev     */
                                              
   proto_register_field_array(proto_babelshark, hf, array_length(hf));
   proto_register_subtree_array(ett, array_length(ett));
}

void
proto_reg_handoff_babelshark(void)
{  
   static dissector_handle_t babelshark_handle;

   babelshark_handle = create_dissector_handle(dissect_babelshark, proto_babelshark);
   dissector_add("udp.port", BABELSHARK_PORT, babelshark_handle);
}

