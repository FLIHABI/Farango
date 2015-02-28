
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

__author__ = 'Snaipe'

from enum import Enum


class AnsiColorCode(Enum):
    def __str__(self):
        return '\033[%dm' % self.value

    def __add__(self, other):
        return str(self) + other

    def __radd__(self, other):
        return other + str(self)


class ForegroundColor(AnsiColorCode):
    black = 30
    red = 31
    green = 32
    yellow = 33
    blue = 34
    magenta = 35
    cyan = 36
    white = 37
    reset = 39


class BackgroundColor(AnsiColorCode):
    black = 40
    red = 41
    green = 42
    yellow = 43
    blue = 44
    magenta = 45
    cyan = 46
    white = 47
    reset = 49


class Color:
    fg = ForegroundColor
    bg = BackgroundColor