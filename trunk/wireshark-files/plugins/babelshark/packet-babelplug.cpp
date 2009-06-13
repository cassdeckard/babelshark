/* packet-babelplug.c
 * Routines for babelplug dissection
 *
 * $Id: packet-babelplug.c 18 2009-06-12 22:22:31Z histumness $
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

// C headers
extern "C" {

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <epan/packet.h>
#include <epan/prefs.h>
#include "packet-babelplug.h"
}

// C++ headers
//#include "test.h"

static int proto_babelplug = -1;
static int hf_babelplug_pdu = -1;
static int hf_babelplug_testtype = -1;

static gint ett_babelplug = -1;
static gint ett_babelplug_test = -1;
static gint ett_babelplug_test2 = -1;

static struct _babelplug_prefs babelplug_preferences = { BABELPLUG_UDP_PORT };

static const value_string babelplug_vals[] = {
   { 1,   "ONE" },
   { 2,   "TWO" },
   { 0,    NULL }
};

static void dissect_babelplug(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
   guint8 packet_type = tvb_get_guint8(tvb, 0);

   if (check_col(pinfo->cinfo, COL_PROTOCOL)) {
      col_set_str(pinfo->cinfo, COL_PROTOCOL, "BABELPLUG");
   }
   /* Clear out stuff in the info column */
   if (check_col(pinfo->cinfo,COL_INFO)) {
      col_clear(pinfo->cinfo,COL_INFO);
   }
   if (check_col(pinfo->cinfo, COL_INFO)) {
       col_add_fstr(pinfo->cinfo, COL_INFO, "TYPE %s",
              val_to_str(packet_type, babelplug_vals, "UNKNOWN (0x%02x)"));
   }


   if (tree) { /* we are being asked for details */
      proto_item *ti = NULL;
      proto_tree *babelplug_tree = NULL;
      proto_tree *babelplug_test_tree = NULL;
      proto_tree *babelplug_test_node = NULL;
      proto_tree *babelplug_test_tree2 = NULL;
      proto_tree *babelplug_test_node2 = NULL;
      gint offset = 0;

      ti = proto_tree_add_item(tree, proto_babelplug, tvb, 0, -1, FALSE);

      /* proto-level text */
      proto_item_append_text(ti, ", Type %s", val_to_str(packet_type, babelplug_vals, "Unknown (0x%02x)"));

      /* subtree */
      babelplug_tree = proto_item_add_subtree(ti, ett_babelplug);
      babelplug_test_node = proto_tree_add_text(babelplug_tree, tvb, 0, 8, "Top level PDU");

      /* another subtree ? */
      babelplug_test_tree = proto_item_add_subtree(babelplug_test_node, ett_babelplug_test);
      proto_tree_add_item(babelplug_test_tree, hf_babelplug_testtype, tvb, offset, 4, FALSE); offset += 4;
      babelplug_test_node2 = proto_tree_add_item(babelplug_test_tree, hf_babelplug_testtype, tvb, offset, 4, FALSE);

      babelplug_test_tree2 = proto_item_add_subtree(babelplug_test_node2, ett_babelplug_test2);
      proto_tree_add_item(babelplug_test_tree2, hf_babelplug_testtype, tvb, offset, 2, FALSE); offset += 2;
      proto_tree_add_text(babelplug_test_tree2, tvb, offset, 2, "this is a test"); offset += 2;
   }

}

void babelplug_prefs_register(struct _babelplug_prefs *prefs, module_t *module)
{
    prefs_register_uint_preference(module,
        "udp_port",
        "UDP Port",
        "Babelplug will be handed off packets that come in on this port",
        10,
        &prefs->udp_port);
}

/* REMEMBER: This is a C function, called directly by Wireshark */
void
proto_reg_handoff_babelplug(void)
{
   static gboolean babelplug_prefs_initialized = FALSE;
   static dissector_handle_t babelplug_handle;
   static struct _babelplug_prefs prev_prefs;

   if (!babelplug_prefs_initialized)
   {
       babelplug_handle = create_dissector_handle(dissect_babelplug, proto_babelplug);
       babelplug_prefs_initialized = TRUE;
   }
   else
   {
       dissector_delete("udp.port", prev_prefs.udp_port, babelplug_handle);
   }

   printf("proto_reg_handoff_babelplug\n");
   printf("udp_port : %u\n", babelplug_preferences.udp_port);
   dissector_add("udp.port", babelplug_preferences.udp_port, babelplug_handle);

   // save previous preferences
   prev_prefs.udp_port = babelplug_preferences.udp_port;
}

/* REMEMBER: This is a C function, called directly by Wireshark */
void
proto_register_babelplug(void)
{
   module_t *module;
   static hf_register_info hf[] = {
      { &hf_babelplug_pdu,
         {"Babelplug defined PDU",
          "babelplug.pdu",
          FT_UINT32, BASE_DEC,
          VALS(babelplug_vals), 0,
          "Babelplug PDU", HFILL
         }
      },
      { &hf_babelplug_testtype,
         {"Babelplug Test Type",
          "babelplug.test",
          FT_UINT32, BASE_DEC,
          NULL, 0,
          "Babelplug TEST", HFILL
         }
      }
   };

   /* Setup protocol subtree array */
   static gint *ett[] = {
      &ett_babelplug,
      &ett_babelplug_test,
      &ett_babelplug_test2
   };

   printf("proto_register_babelplug\n");
   proto_babelplug = proto_register_protocol("Babelplug",  /* name       */
                                              "Babelplug",  /* short name */
                                              "babelplug"); /* abbrev     */

   proto_register_field_array(proto_babelplug, hf, array_length(hf));
   proto_register_subtree_array(ett, array_length(ett));

   /* preferences */
   module = prefs_register_protocol(proto_babelplug, proto_reg_handoff_babelplug);
   babelplug_prefs_register(&babelplug_preferences, module);
}
