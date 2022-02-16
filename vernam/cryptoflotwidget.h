#ifndef CRYPTOFLOTWIDGET_H
#define CRYPTOFLOTWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QTextEdit>
#include <QGroupBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "cryptosystemFlot.h"

class CryptoFlotWidget : public QWidget
{
    Q_OBJECT

public:
    CryptoFlotWidget(QWidget *parent = nullptr);
    ~CryptoFlotWidget();
};
#endif // CRYPTOFLOTWIDGET_H
