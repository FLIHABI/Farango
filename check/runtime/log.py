from colors import Color

def info(msg):
    log('[----------]: ', Color.fg.green, msg)


def important(msg):
    log('[==========]: ', Color.fg.green, msg)


def error(msg):
    log('', Color.fg.red, msg)


def log(prefix, color, msg):
    print(color + prefix + msg + Color.fg.reset + Color.bg.reset)
