/********************************************************************************
** Form generated from reading UI file 'intro2.ui'
**
** Created: Sat 25. Sep 14:32:00 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTRO2_H
#define UI_INTRO2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Intro2
{
public:
    QGraphicsView *graphicsView;
    QLabel *ApplLabel;
    QLabel *ApplLabel_2;

    void setupUi(QWidget *Intro2)
    {
        if (Intro2->objectName().isEmpty())
            Intro2->setObjectName(QString::fromUtf8("Intro2"));
        Intro2->resize(640, 480);
        graphicsView = new QGraphicsView(Intro2);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(30, 120, 81, 71));
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
        ApplLabel = new QLabel(Intro2);
        ApplLabel->setObjectName(QString::fromUtf8("ApplLabel"));
        ApplLabel->setGeometry(QRect(10, 20, 601, 81));
        QFont font;
        font.setPointSize(22);
        ApplLabel->setFont(font);
        ApplLabel_2 = new QLabel(Intro2);
        ApplLabel_2->setObjectName(QString::fromUtf8("ApplLabel_2"));
        ApplLabel_2->setGeometry(QRect(20, 400, 601, 81));
        QFont font1;
        font1.setPointSize(19);
        ApplLabel_2->setFont(font1);

        retranslateUi(Intro2);

        QMetaObject::connectSlotsByName(Intro2);
    } // setupUi

    void retranslateUi(QWidget *Intro2)
    {
        Intro2->setWindowTitle(QApplication::translate("Intro2", "Form", 0, QApplication::UnicodeUTF8));
        ApplLabel->setText(QApplication::translate("Intro2", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:22pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#ffffff;\">Please visit my website for more information</span></p>\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:18pt; color:#ffffff;\">http://www.plaatsoft.nl</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        ApplLabel_2->setText(QApplication::translate("Intro2", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:19pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; font-weight:600; color:#ffffff;\">RedSquare is also available for Nintendo Wii</span></p></body></html>", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Intro2: public Ui_Intro2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTRO2_H
