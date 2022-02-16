#include "mainwindow.h"
#include "adfgvxWidget.h"
#include "vigenereWidget.h"
#include "playfairWidget.h"

#include <QToolBar>
#include <QComboBox>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Tool bar
    auto toolBar = new QToolBar();
    auto widgetToolBar = new QWidget();
    auto labelToolBar = new QLabel("Chiffrement");
    auto comboxToolBar = new QComboBox();
    QStringList lsSysteme = {"ADFGVX", "Vigenere", "Playfair"};
    comboxToolBar->addItems(lsSysteme);
    widgetToolBar->setLayout(new QHBoxLayout);
    widgetToolBar->layout()->addWidget(labelToolBar);
    widgetToolBar->layout()->addWidget(comboxToolBar);
    widgetToolBar->layout()->setAlignment(Qt::AlignCenter);
    toolBar->addWidget(widgetToolBar);
    addToolBar(toolBar);

    //Central widget
    m_centralWidget = new QStackedWidget();
    auto adfgvxWidget = new AdfgvxWidget();
    auto vigenereWidget = new VigenereWidget();
    auto playfairWidget = new PlayfairWidget();
    m_centralWidget->addWidget(adfgvxWidget);
    m_centralWidget->addWidget(vigenereWidget);
    m_centralWidget->addWidget(playfairWidget);
    setCentralWidget(m_centralWidget);
    auto me = this;

    //Action menu
    menuBar()->addAction(tr("Vigenere"), this, [me, vigenereWidget](){me->m_centralWidget->setCurrentWidget(vigenereWidget);});
    menuBar()->addAction(tr("ADFGVX"), this, [me, adfgvxWidget](){me->m_centralWidget->setCurrentWidget(adfgvxWidget);});
    menuBar()->addAction(tr("Playfair"), this, [me, playfairWidget](){me->m_centralWidget->setCurrentWidget(playfairWidget);});

    //Connexion
    connect(comboxToolBar, SIGNAL(currentIndexChanged(int)), this, SLOT(setCurrentIndex(int)));
}

MainWindow::~MainWindow()
{
}

void MainWindow::setCurrentIndex(int index)
{
    m_centralWidget->setCurrentIndex(index);
}

