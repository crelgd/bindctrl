"""
MIT License
Copyright (c) 2026 crelgd
"""

from PySide6 import QtCore, QtWidgets

import sys
import subprocess

class Main(QtWidgets.QWidget):
    def __init__(self):
        super().__init__()

        self.text = QtWidgets.QLabel("Hello World",
                                     alignment=QtCore.Qt.AlignCenter)

        self.bStart = QtWidgets.QPushButton("Start")
        self.bStop = QtWidgets.QPushButton("Stop")

        self.layout = QtWidgets.QVBoxLayout()
        self.layout.addWidget(self.text)
        self.layout.addWidget(self.bStart)
        self.layout.addWidget(self.bStop)
        self.setLayout(self.layout)

        self.bStart.clicked.connect(self.ClientEnable)
        self.bStart.clicked.connect(self.ClientDisable)

    @QtCore.Slot()
    def ClientEnable(self):
        self.client = subprocess.run(["trtgp.exe"])
    
    @QtCore.Slot()
    def ClientDisable(self):
        if (self.client):
            self.client.kill()
