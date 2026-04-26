"""
MIT License
Copyright (c) 2026 crelgd
"""

import ctypes
import sys

def returnErr(str):
    ctypes.windll.user32.MessageBoxW(None, str, "err", 0)
    sys.exit()
    