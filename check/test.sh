#!/bin/sh
SCRIPT_PATH=$(dirname $(readlink -f "$0"))
python3 "$SCRIPT_PATH/runtime/test.py" --binary fgc "$@"
