"""
MIT License
Copyright (c) 2026 crelgd
"""

from PySide6 import QtCore, QtWidgets
from dbg import returnErr

import sys
import os
import subprocess

class Main(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

        self.client = None

        self.bStart = QtWidgets.QPushButton("Start")
        self.bStop = QtWidgets.QPushButton("Stop")

        self.layout = QtWidgets.QVBoxLayout()
        self.layout.addWidget(self.bStart)
        self.layout.addWidget(self.bStop)
        self.setLayout(self.layout)

        self.bStart.clicked.connect(self.ClientEnable)
        self.bStop.clicked.connect(self.ClientDisable)

    @QtCore.Slot()
    def ClientEnable(self):
        if (os.path.isfile("trtgp.exe")):
            self.client = subprocess.Popen(["trtgp.exe"])
        else:
            returnErr("trtgp.exe not found")
    
    @QtCore.Slot()
    def ClientDisable(self):
        if (self.client != None):
            try:
                self.client.kill()
            except Exception:
                pass
            self.client = None
