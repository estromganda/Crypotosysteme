#include "vigenereWidget.h"

VigenereWidget::VigenereWidget(QWidget *parent)
    : QMainWindow(parent)
{
    auto title = new QLabel("<span style='color: blue'>"+tr("Cryptosysteme de Viginer")+"</span>");
    QLabel* labelTextInit = new QLabel("Texte claire"),
            *labelTexteFinale = new QLabel(tr("Cryptogramme"));
    title->setAlignment(Qt::AlignHCenter);
    title->setFont(QFont("", 25, -1, true));
    auto groupeBox = new QGroupBox(tr("Action"));
    auto password = new QLineEdit();
    auto btnEncrypt = new QRadioButton(tr("Cryptage")); //btnEncrypt->setChecked(true);
    auto btnDecrypt = new QRadioButton(tr("Décryptage")); btnDecrypt->setChecked(true);
    auto textInit = new QTextEdit();
    auto textFinal = new QTextEdit();
    auto btnSubmit = new QPushButton("Crypter");

    password->setPlaceholderText(tr("Mot de passe"));

    groupeBox->setLayout(new QHBoxLayout());
    groupeBox->layout()->addWidget(btnEncrypt);
    groupeBox->layout()->addWidget(btnDecrypt);
    auto lF = new QFormLayout();
    lF->addWidget(title);
    lF->addWidget(groupeBox);
    lF->addWidget(password);
    lF->addRow(labelTextInit);
    lF->addWidget(textInit);
    lF->addWidget(btnSubmit);
    lF->addWidget(labelTexteFinale);
    lF->addWidget(textFinal);
    lF->setAlignment(btnSubmit, Qt::AlignCenter);
    setCentralWidget(new QWidget());
    centralWidget()->setLayout(lF);

    //Connexion
    connect(btnEncrypt, &QRadioButton::toggled, this, [btnSubmit, labelTextInit, labelTexteFinale](bool v){
       if(v){
           labelTextInit->setText(tr("Texte crypté"));
           labelTexteFinale->setText(tr("Cryptogramme"));
           btnSubmit->setText(tr("Crypter"));
       }else{
           labelTextInit->setText(tr("Cryptogramme"));
           labelTexteFinale->setText(tr("Texte crypté"));
           btnSubmit->setText(tr("Décrypter"));
       }
    });
    auto me = this;
    connect(btnSubmit, &QPushButton::clicked, this, [me, textInit, textFinal, password, btnEncrypt](){
        if(textInit->toPlainText().isEmpty()) return ;
        if(password->text().isEmpty()){
            QMessageBox::information(me, "", tr("Veuillez entrez un mot de passe svp"));
            return ;
        }
        if(btnEncrypt->isChecked()){
            auto txt = Vigenere::encrypt(textInit->toPlainText().toStdString(), password->text().toStdString());
            textFinal->setText(txt.c_str());
        }else{
            std::string txt = Vigenere::decrypt(textInit->toPlainText().toStdString(), password->text().toStdString());
            textFinal->setText(txt.c_str());
        }
    });
}

VigenereWidget::~VigenereWidget()
{
}

