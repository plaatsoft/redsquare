/********************************************************************************
** Form generated from reading UI file 'releasenotes.ui'
**
** Created: Sat 25. Sep 16:32:41 2010
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RELEASENOTES_H
#define UI_RELEASENOTES_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ReleaseNotes
{
public:
    QLabel *label;
    QGraphicsView *graphicsView;
    QPushButton *backButton;
    QTextEdit *textEdit;

    void setupUi(QWidget *ReleaseNotes)
    {
        if (ReleaseNotes->objectName().isEmpty())
            ReleaseNotes->setObjectName(QString::fromUtf8("ReleaseNotes"));
        ReleaseNotes->resize(640, 480);
        label = new QLabel(ReleaseNotes);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(120, 20, 391, 71));
        QFont font;
        font.setPointSize(40);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        graphicsView = new QGraphicsView(ReleaseNotes);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(20, 10, 81, 71));
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
        backButton = new QPushButton(ReleaseNotes);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(230, 430, 161, 31));
        textEdit = new QTextEdit(ReleaseNotes);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 100, 591, 301));
        QFont font1;
        font1.setPointSize(14);
        textEdit->setFont(font1);
        textEdit->setAutoFillBackground(true);
        textEdit->setFrameShape(QFrame::NoFrame);
        textEdit->setFrameShadow(QFrame::Plain);
        textEdit->setReadOnly(true);
        graphicsView->raise();
        label->raise();
        backButton->raise();
        textEdit->raise();

        retranslateUi(ReleaseNotes);

        QMetaObject::connectSlotsByName(ReleaseNotes);
    } // setupUi

    void retranslateUi(QWidget *ReleaseNotes)
    {
        ReleaseNotes->setWindowTitle(QApplication::translate("ReleaseNotes", "Form", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("ReleaseNotes", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:40pt; font-weight:600; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#ffffff;\">Release Notes</span></p></body></html>", 0, QApplication::UnicodeUTF8));
        backButton->setText(QApplication::translate("ReleaseNotes", "Back", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ReleaseNotes: public Ui_ReleaseNotes {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RELEASENOTES_H
