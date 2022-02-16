#ifndef VIGENEREWIDGET_H
#define VIGENEREWIDGET_H

#include <QMainWindow>
#include <QTextEdit>
#include <QGroupBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "vigenere.h"

class VigenereWidget : public QMainWindow
{
    Q_OBJECT

public:
    VigenereWidget(QWidget *parent = nullptr);
    static QString P;

    ~VigenereWidget();
};
#endif // VIGENEREWIDGET_H
