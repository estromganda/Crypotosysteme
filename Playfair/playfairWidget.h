#ifndef PLAYFAIRWIDGET_H
#define PLAYFAIRWIDGET_H

#include <QSplitter>
#include <QTextEdit>
#include <QGroupBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include "playfair.h"

class PlayfairWidget : public QWidget
{
    Q_OBJECT

public:
    PlayfairWidget(QWidget *parent = nullptr);
    ~PlayfairWidget();
};
#endif // PLAYFAIRWIDGET_H
