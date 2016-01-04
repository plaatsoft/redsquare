/********************************************************************************
** Form generated from reading UI file 'mainmenu.ui'
**
** Created: Sat 25. Sep 15:32:43 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINMENU_H
#define UI_MAINMENU_H

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

class Ui_MainMenu
{
public:
    QLabel *ApplLabel;
    QLabel *dateLabel;
    QPushButton *playButton;
    QPushButton *creditsButton;
    QGraphicsView *graphicsView;
    QPushButton *helpButton;
    QPushButton *releasenotesButton;
    QPushButton *scoreButton;
    QPushButton *exitButton;
    QPushButton *donateButton;
    QLabel *newversionLabel;

    void setupUi(QWidget *MainMenu)
    {
        if (MainMenu->objectName().isEmpty())
            MainMenu->setObjectName(QString::fromUtf8("MainMenu"));
        MainMenu->resize(640, 480);
        ApplLabel = new QLabel(MainMenu);
        ApplLabel->setObjectName(QString::fromUtf8("ApplLabel"));
        ApplLabel->setGeometry(QRect(30, 20, 261, 41));
        QFont font;
        font.setPointSize(22);
        ApplLabel->setFont(font);
        dateLabel = new QLabel(MainMenu);
        dateLabel->setObjectName(QString::fromUtf8("dateLabel"));
        dateLabel->setGeometry(QRect(30, 60, 221, 21));
        QFont font1;
        font1.setPointSize(15);
        dateLabel->setFont(font1);
        playButton = new QPushButton(MainMenu);
        playButton->setObjectName(QString::fromUtf8("playButton"));
        playButton->setGeometry(QRect(450, 30, 161, 31));
        creditsButton = new QPushButton(MainMenu);
        creditsButton->setObjectName(QString::fromUtf8("creditsButton"));
        creditsButton->setGeometry(QRect(450, 150, 161, 31));
        graphicsView = new QGraphicsView(MainMenu);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(20, 100, 81, 71));
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
        helpButton = new QPushButton(MainMenu);
        helpButton->setObjectName(QString::fromUtf8("helpButton"));
        helpButton->setGeometry(QRect(450, 110, 161, 31));
        releasenotesButton = new QPushButton(MainMenu);
        releasenotesButton->setObjectName(QString::fromUtf8("releasenotesButton"));
        releasenotesButton->setGeometry(QRect(450, 190, 161, 31));
        scoreButton = new QPushButton(MainMenu);
        scoreButton->setObjectName(QString::fromUtf8("scoreButton"));
        scoreButton->setGeometry(QRect(450, 70, 161, 31));
        exitButton = new QPushButton(MainMenu);
        exitButton->setObjectName(QString::fromUtf8("exitButton"));
        exitButton->setGeometry(QRect(450, 420, 161, 31));
        donateButton = new QPushButton(MainMenu);
        donateButton->setObjectName(QString::fromUtf8("donateButton"));
        donateButton->setGeometry(QRect(450, 230, 161, 31));
        newversionLabel = new QLabel(MainMenu);
        newversionLabel->setObjectName(QString::fromUtf8("newversionLabel"));
        newversionLabel->setGeometry(QRect(30, 330, 441, 61));
        newversionLabel->setFont(font1);
        graphicsView->raise();
        ApplLabel->raise();
        dateLabel->raise();
        playButton->raise();
        creditsButton->raise();
        helpButton->raise();
        releasenotesButton->raise();
        scoreButton->raise();
        exitButton->raise();
        donateButton->raise();
        newversionLabel->raise();
        QWidget::setTabOrder(playButton, scoreButton);
        QWidget::setTabOrder(scoreButton, helpButton);
        QWidget::setTabOrder(helpButton, creditsButton);
        QWidget::setTabOrder(creditsButton, releasenotesButton);
        QWidget::setTabOrder(releasenotesButton, donateButton);
        QWidget::setTabOrder(donateButton, exitButton);
        QWidget::setTabOrder(exitButton, graphicsView);

        retranslateUi(MainMenu);

        QMetaObject::connectSlotsByName(MainMenu);
    } // setupUi

    void retranslateUi(QWidget *MainMenu)
    {
        MainMenu->setWindowTitle(QApplication::translate("MainMenu", "Form", 0, QApplication::UnicodeUTF8));
        ApplLabel->setText(QApplication::translate("MainMenu", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:22pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600; color:#000000;\">RedSquare vX.X</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        dateLabel->setText(QApplication::translate("MainMenu", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:15pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; color:#000000;\">xx-xx-xxxx</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        playButton->setText(QApplication::translate("MainMenu", "Play", 0, QApplication::UnicodeUTF8));
        creditsButton->setText(QApplication::translate("MainMenu", "Credits", 0, QApplication::UnicodeUTF8));
        helpButton->setText(QApplication::translate("MainMenu", "Help", 0, QApplication::UnicodeUTF8));
        releasenotesButton->setText(QApplication::translate("MainMenu", "Release Notes", 0, QApplication::UnicodeUTF8));
        scoreButton->setText(QApplication::translate("MainMenu", "High Score", 0, QApplication::UnicodeUTF8));
        exitButton->setText(QApplication::translate("MainMenu", "Exit", 0, QApplication::UnicodeUTF8));
        donateButton->setText(QApplication::translate("MainMenu", "Donate", 0, QApplication::UnicodeUTF8));
        newversionLabel->setText(QApplication::translate("MainMenu", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:15pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainMenu: public Ui_MainMenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINMENU_H
