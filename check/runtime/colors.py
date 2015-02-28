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