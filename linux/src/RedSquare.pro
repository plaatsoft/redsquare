# -------------------------------------------------
# Project created by QtCreator 2010-03-30T06:50:34
# -------------------------------------------------
QT += network \
    xml
TARGET = RedSquare
TEMPLATE = app
SOURCES +=  main.cpp \
    Square.cpp \
    mainmenu.cpp \
    credits.cpp \
    help.cpp \
    donate.cpp \
    intro.cpp \
    intro2.cpp \
    HighScore.cpp \
    score.cpp \
    releasenotes.cpp \
    gameboard.cpp \
    intro3.cpp

HEADERS += Square.h \
    General.h \
    mainmenu.h \
    credits.h \
    help.h \
    donate.h \
    intro.h \
    intro2.h \
    HighScore.h \
    score.h \
    releasenotes.h \
    gameboard.h \
    intro3.h

FORMS += mainmenu.ui \
    credits.ui \
    help.ui \
    donate.ui \
    intro.ui \
    intro2.ui \
    score.ui \
    releasenotes.ui \
    gameboard.ui \
    intro3.ui

RESOURCES += resources.qrc
RC_FILE = RedSquare.rc
