"""
MIT License
Copyright (c) 2026 crelgd
"""

from PySide6 import QtCore, QtWidgets

from launcher import widgets
import sys

app = QtWidgets.QApplication([])

main = widgets.Main()
main.resize(200, 100)
main.show()

sys.exit(app.exec_())
