/********************************************************************************
** Form generated from reading UI file 'gameboard.ui'
**
** Created: Sun 20. Mar 18:28:23 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEBOARD_H
#define UI_GAMEBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameBoard
{
public:
    QLabel *gameOverText;
    QLabel *playTimeText;
    QPushButton *backButton;
    QLabel *scoreValue2;
    QLabel *highScoreText;
    QGraphicsView *graphicsView;
    QLabel *timeValueText;
    QLabel *scoreValue1;
    QLabel *playTimeValue;
    QLabel *scoreText;

    void setupUi(QWidget *GameBoard)
    {
        if (GameBoard->objectName().isEmpty())
            GameBoard->setObjectName(QString::fromUtf8("GameBoard"));
        GameBoard->resize(640, 480);
        gameOverText = new QLabel(GameBoard);
        gameOverText->setObjectName(QString::fromUtf8("gameOverText"));
        gameOverText->setGeometry(QRect(150, 90, 331, 71));
        QFont font;
        font.setPointSize(40);
        font.setBold(true);
        font.setWeight(75);
        gameOverText->setFont(font);
        playTimeText = new QLabel(GameBoard);
        playTimeText->setObjectName(QString::fromUtf8("playTimeText"));
        playTimeText->setGeometry(QRect(240, 160, 141, 31));
        QFont font1;
        font1.setPointSize(20);
        font1.setBold(true);
        font1.setWeight(75);
        playTimeText->setFont(font1);
        backButton = new QPushButton(GameBoard);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(240, 390, 161, 31));
        scoreValue2 = new QLabel(GameBoard);
        scoreValue2->setObjectName(QString::fromUtf8("scoreValue2"));
        scoreValue2->setGeometry(QRect(270, 270, 101, 31));
        scoreValue2->setFont(font1);
        highScoreText = new QLabel(GameBoard);
        highScoreText->setObjectName(QString::fromUtf8("highScoreText"));
        highScoreText->setGeometry(QRect(70, 310, 531, 61));
        highScoreText->setFont(font1);
        graphicsView = new QGraphicsView(GameBoard);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(10, 30, 81, 71));
        graphicsView->setAutoFillBackground(false);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::NoBrush);
        graphicsView->setBackgroundBrush(brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::NoBrush);
        graphicsView->setForegroundBrush(brush1);
        graphicsView->setInteractive(true);
        timeValueText = new QLabel(GameBoard);
        timeValueText->setObjectName(QString::fromUtf8("timeValueText"));
        timeValueText->setGeometry(QRect(270, 10, 81, 20));
        scoreValue1 = new QLabel(GameBoard);
        scoreValue1->setObjectName(QString::fromUtf8("scoreValue1"));
        scoreValue1->setGeometry(QRect(10, 10, 81, 20));
        playTimeValue = new QLabel(GameBoard);
        playTimeValue->setObjectName(QString::fromUtf8("playTimeValue"));
        playTimeValue->setGeometry(QRect(240, 190, 141, 31));
        playTimeValue->setFont(font1);
        scoreText = new QLabel(GameBoard);
        scoreText->setObjectName(QString::fromUtf8("scoreText"));
        scoreText->setGeometry(QRect(270, 240, 101, 31));
        scoreText->setFont(font1);
        graphicsView->raise();
        gameOverText->raise();
        playTimeText->raise();
        backButton->raise();
        scoreValue2->raise();
        highScoreText->raise();
        timeValueText->raise();
        scoreValue1->raise();
        playTimeValue->raise();
        scoreText->raise();

        retranslateUi(GameBoard);

        QMetaObject::connectSlotsByName(GameBoard);
    } // setupUi

    void retranslateUi(QWidget *GameBoard)
    {
        GameBoard->setWindowTitle(QApplication::translate("GameBoard", "Form", 0, QApplication::UnicodeUTF8));
        gameOverText->setText(QApplication::translate("GameBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:40pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ffffff;\">GAME OVER</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        playTimeText->setText(QApplication::translate("GameBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:20pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ffffff;\">Play Time</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        backButton->setText(QApplication::translate("GameBoard", "Back", 0, QApplication::UnicodeUTF8));
        scoreValue2->setText(QApplication::translate("GameBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:20pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ffffff;\">Score</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        highScoreText->setText(QApplication::translate("GameBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:20pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ffffff;\">Player 1 win, 1th place in highscore!</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        timeValueText->setText(QApplication::translate("GameBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#ffffff;\">time</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        scoreValue1->setText(QApplication::translate("GameBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#ffffff;\">score</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        playTimeValue->setText(QApplication::translate("GameBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:20pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ffffff;\">Play Time</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        scoreText->setText(QApplication::translate("GameBoard", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:20pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ffffff;\">Score</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GameBoard: public Ui_GameBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEBOARD_H
