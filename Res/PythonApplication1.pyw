import sys
from PyQt5 import QtNetwork
from PyQt5.QtCore import QCoreApplication, QUrl
from PyQt5 import QtWidgets,QtGui,QtCore
from PyQt5.QtWebEngineWidgets import *

from PyQt5.QtCore import QDate, QTime, QDateTime, Qt
import sys
from PyQt5.QtCore import QUrl
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import (QApplication, QLineEdit, QMainWindow, 
    QPushButton, QToolBar)
from PyQt5.QtWebEngineWidgets import QWebEnginePage, QWebEngineView
import sys, os, platform

if platform.system() ==  "Windows":
    import win32pipe, win32file

class MainWindow(QMainWindow):
    def __init__(self, *args, **kwargs):
        QMainWindow.__init__(self, *args, **kwargs)
        self.webview = QWebEngineView()
        profile = QWebEngineProfile("storage", self.webview)
        cookie_store = profile.cookieStore()
        cookie_store.cookieAdded.connect(self.onCookieAdded)
        self.cookies = []
        webpage = QWebEnginePage(profile, self.webview)
        self.webview.setPage(webpage)
        self.webview.load(
            QUrl("https://leetcode.com/accounts/login/"))
        self.webview.loadFinished.connect(self.loadFinishedHandler)
        self.setCentralWidget(self.webview)

    def loadFinishedHandler(self):
        hasSessionToken = False

        for c in self.cookies:
            if c.name() == "LEETCODE_SESSION":
                hasSessionToken = True
        
        if hasSessionToken == True:
            self.saveToFile()
            self.close()
        else:
            self.show()

    def onCookieAdded(self, cookie):
        self.cookies.append(QtNetwork.QNetworkCookie(cookie))

    def saveToFile(self):
        out = open("cookies", "w")
        for c in self.cookies:
            out.write(bytearray(c.name()).decode() + "=" + bytearray(c.value()).decode() + '\n')
        out.close()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    w = MainWindow()
    sys.exit(app.exec_())