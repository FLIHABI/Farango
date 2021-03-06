#!/bin/sh
#
# This file is part of Farango.
#
# Copyright (c) 2015 FLIHABI.
#
# Farango is licensed under the FLIHABI License Version 1.
#
# Farango is free software: you can redistribute it and/or modify it under
# the terms of the GNU Lesser General Public License as published by the Free
# Software Foundation, either version 3 of the License, or (at your option)
# any later version.
#
# In addition, 180 days after any changes are published, you can use the
# software, incorporating those changes, under the terms of the MIT license,
# as described in the FLIHABI License Version 1.
#
# Farango is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
# FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
# more details.
#
# You should have received a copy of the GNU Lesser General Public License,
# the MIT license and the FLIHABI License Version 1 along with this program.
# If not, see <http://www.gnu.org/licenses/> for the GNU Lesser General Public
# License and see <http://goo.gl/t8dfl6> for the full license, including
# the MIT license.
#
SCRIPT_PATH=$(dirname $(readlink -f "$0"))
python3 "$SCRIPT_PATH/runtime/test.py" --binary fgc "$@"
