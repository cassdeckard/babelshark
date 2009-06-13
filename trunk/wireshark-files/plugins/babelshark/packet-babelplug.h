/* packet-babelplug.h
 *
 * $Id: packet-babelplug.h 18 2009-06-12 22:22:31Z histumness $
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

#ifndef PACKET_BABELPLUG_H
#define PACKET_BABELPLUG_H

#define BABELPLUG_UDP_PORT 443

struct _babelplug_prefs
{
    guint udp_port;
};

void babelplug_prefs_register(struct _babelplug_prefs *prefs, module_t *module);

// these functions must be defined here as extern "C"
// but this header should be read in as extern "C" by packet-babelplug.cpp anyway
// so no worries!
void proto_register_babelplug(void);
void proto_reg_handoff_babelplug(void);

#endif
