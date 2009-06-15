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

static struct _babelshark_prefs babelshark_preferences = { BABELSHARK_UDP_PORT,
                                                           BABELSHARK_IN_FILE };

static void create_dissector()
{
   // Create Dissector
   babelshark_dissector = new BabelShark::Dissector(babelshark_preferences.in_file, &proto_babelshark);

}

static void update_dissector(const char* inFile)
{
   // Create Dissector
   babelshark_dissector->ReparseTree(inFile);

}

static void dissect_babelshark(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree)
{
    babelshark_dissector->Test(); // TODO: Remove
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

    prefs_register_string_preference(module,
        "pdi_file",
        "Input PDI file",
        "File in PDI format describing the packet structure",
        &prefs->in_file);
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
       update_dissector(babelshark_preferences.in_file);
   }

   printf("proto_reg_handoff_babelshark\n");
   printf("udp_port : %u\n", babelshark_preferences.udp_port);
   dissector_add("udp.port", babelshark_preferences.udp_port, babelshark_handle);

   // save previous udp port
   prev_prefs.udp_port = babelshark_preferences.udp_port;
}

/* REMEMBER: This is a C function, called directly by Wireshark */
void
proto_register_babelshark(void)
{
   module_t *module;

   create_dissector();

   /* preferences */
   module = prefs_register_protocol(proto_babelshark, proto_reg_handoff_babelshark);
   babelshark_prefs_register(&babelshark_preferences, module);
}
