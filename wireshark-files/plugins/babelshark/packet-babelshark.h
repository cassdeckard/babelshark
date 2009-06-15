/* packet-babelshark.h
 *
 * $Id: packet-babelshark.h 18 2009-06-12 22:22:31Z histumness $
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

#ifndef PACKET_BABELSHARK_H
#define PACKET_BABELSHARK_H

#define BABELSHARK_UDP_PORT 443
#define BABELSHARK_IN_FILE  "babelshark.pdi"

#include "Dissector.h"

static BabelShark::Dissector* babelshark_dissector;

struct _babelshark_prefs
{
    guint       udp_port;
    const char* in_file;
};

void babelshark_prefs_register(struct _babelshark_prefs *prefs, module_t *module);

// these functions must be defined here as extern "C"
extern "C"
{
    void proto_register_babelshark(void);
    void proto_reg_handoff_babelshark(void);
}

#endif
