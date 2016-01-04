/********************************************************************************
** Form generated from reading UI file 'intro3.ui'
**
** Created: Sun 20. Mar 18:51:11 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTRO3_H
#define UI_INTRO3_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Intro3
{
public:
    QGraphicsView *graphicsView;
    QLabel *ApplLabel;

    void setupUi(QWidget *Intro3)
    {
        if (Intro3->objectName().isEmpty())
            Intro3->setObjectName(QString::fromUtf8("Intro3"));
        Intro3->resize(640, 482);
        graphicsView = new QGraphicsView(Intro3);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(30, 30, 81, 71));
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
        ApplLabel = new QLabel(Intro3);
        ApplLabel->setObjectName(QString::fromUtf8("ApplLabel"));
        ApplLabel->setGeometry(QRect(10, 110, 611, 251));
        QFont font;
        font.setPointSize(22);
        ApplLabel->setFont(font);

        retranslateUi(Intro3);

        QMetaObject::connectSlotsByName(Intro3);
    } // setupUi

    void retranslateUi(QWidget *Intro3)
    {
        Intro3->setWindowTitle(QApplication::translate("Intro3", "Form", 0, QApplication::UnicodeUTF8));
        ApplLabel->setText(QApplication::translate("Intro3", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:22pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:28pt; color:#ffffff;\">WarQuest is available</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#ffffff;\">visit</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#ffffff;\">http://www.warquest.nl</span></p>\n"
"<p align=\"center\" style=\"-"
                        "qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:18pt; color:#ffffff;\"></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#ffffff;\">and enter the battle zone!</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Intro3: public Ui_Intro3 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTRO3_H
