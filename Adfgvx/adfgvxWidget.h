#ifndef ADFGVXWIDGET_H
#define ADFGVXWIDGET_H

#include <QMainWindow>
#include <QMainWindow>
#include <QTextEdit>
#include <QGroupBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QSplitter>
#include "adfgvx.h"

class AdfgvxWidget : public QMainWindow
{
    Q_OBJECT

public:
    AdfgvxWidget(QWidget *parent = nullptr);
    ~AdfgvxWidget();
};
#endif // ADFGVXWIDGET_H
