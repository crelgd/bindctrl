"""
MIT License
Copyright (c) 2026 crelgd
"""

from PySide6 import QtCore, QtWidgets

import widgets
import sys

if __name__ == "__main__":
    app = QtWidgets.QApplication([])

    main = widgets.Main()
    main.resize(200, 100)
    main.show()

    sys.exit(app.exec())
