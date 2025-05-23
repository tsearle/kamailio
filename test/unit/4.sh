#!/bin/sh
# test basic fifo functionality

# Copyright (C) 2007 1&1 Internet AG
#
# This file is part of Kamailio, a free SIP server.
#
# Kamailio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version
#
# Kamailio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

. include/common
. include/require.sh

CFG=4.cfg

if ! (check_kamailio); then
	exit 0
fi ;

# set up config
printf "loadmodule \"jsonrpcs.so\"\n" > $CFG
printf "modparam(\"jsonrpcs\", \"transport\", 2)\n" >> $CFG
printf "modparam(\"jsonrpcs\", \"fifo_name\", \"$RPCFIFOPATH\")\n" >> $CFG
printf "\nrequest_route {\n ;\n}" >> $CFG

$BIN -L $MOD_DIR -Y $RUN_DIR -P $PIDFILE -w . -f $CFG > /dev/null
ret=$?

if [ "$ret" -eq 0 ] ; then
	sleep 1
	$CTL rpc core.version > /dev/null
	ret=$?
fi ;

kill_kamailio

rm -f $CFG

exit $ret
