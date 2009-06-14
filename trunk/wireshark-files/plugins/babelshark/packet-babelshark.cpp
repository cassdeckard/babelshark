/* packet-babelshark.c
 * Routines for babelshark dissection
 *
 * $Id: packet-babelshark.c 18 2009-06-12 22:22:31Z histumness $
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
}

// C++ headers
#include "packet-babelshark.h"

static int proto_babelshark = -1;
static int hf_babelshark_pdu = -1;
static int hf_babelshark_testtype = -1;

static gint ett_babelshark = -1;
static gint ett_babelshark_test = -1;
static gint ett_babelshark_test2 = -1;

static struct _babelshark_prefs babelshark_preferences = { BABELSHARK_UDP_PORT };

static const value_string babelshark_vals[] = {
   { 1,   "ONE" },
   { 2,   "TWO" },
   { 0,    NULL }
};

static void create_dissector(gint *ett, int proto)
{
    babelshark_dissector = new BabelShark::Dissector(ett, proto);
}

static void dissect_babelshark(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    babelshark_dissector->Test();
    babelshark_dissector->Dissect(tvb, pinfo, tree);
}

void babelshark_prefs_register(struct _babelshark_prefs *prefs, module_t *module)
{
    prefs_register_uint_preference(module,
        "udp_port",
        "UDP Port",
        "Babelshark will be handed off packets that come in on this port",
        10,
        &prefs->udp_port);
}

/* REMEMBER: This is a C function, called directly by Wireshark */
void
proto_reg_handoff_babelshark(void)
{
   static gboolean babelshark_prefs_initialized = FALSE;
   static dissector_handle_t babelshark_handle;
   static struct _babelshark_prefs prev_prefs;

   if (!babelshark_prefs_initialized)
   {
       babelshark_handle = create_dissector_handle(dissect_babelshark, proto_babelshark);
       babelshark_prefs_initialized = TRUE;
   }
   else
   {
       dissector_delete("udp.port", prev_prefs.udp_port, babelshark_handle);
   }

   printf("proto_reg_handoff_babelshark\n");
   printf("udp_port : %u\n", babelshark_preferences.udp_port);
   dissector_add("udp.port", babelshark_preferences.udp_port, babelshark_handle);

   // save previous preferences
   prev_prefs.udp_port = babelshark_preferences.udp_port;
}

/* REMEMBER: This is a C function, called directly by Wireshark */
void
proto_register_babelshark(void)
{
   module_t *module;
   static hf_register_info hf[] = {
      { &hf_babelshark_pdu,
         {"Babelshark defined PDU",
          "babelshark.pdu",
          FT_UINT32, BASE_DEC,
          VALS(babelshark_vals), 0,
          "Babelshark PDU", HFILL
         }
      },
      { &hf_babelshark_testtype,
         {"Babelshark Test Type",
          "babelshark.test",
          FT_UINT32, BASE_DEC,
          NULL, 0,
          "Babelshark TEST", HFILL
         }
      }
   };

   /* Setup protocol subtree array */
   static gint *ett[] = {
      &ett_babelshark,
      &ett_babelshark_test,
      &ett_babelshark_test2
   };

   printf("proto_register_babelshark\n");
   proto_babelshark = proto_register_protocol("Babelshark",  /* name       */
                                              "Babelshark",  /* short name */
                                              "babelshark"); /* abbrev     */

   create_dissector(&ett_babelshark, proto_babelshark);

   proto_register_field_array(proto_babelshark, hf, array_length(hf));
   proto_register_subtree_array(ett, array_length(ett));

   /* preferences */
   module = prefs_register_protocol(proto_babelshark, proto_reg_handoff_babelshark);
   babelshark_prefs_register(&babelshark_preferences, module);
}
