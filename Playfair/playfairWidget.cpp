#include "playfairWidget.h"
#include <QRegularExpressionValidator>

PlayfairWidget::PlayfairWidget(QWidget *parent)
    : QWidget(parent)
{
    //Entete
    auto label = new QLabel("<span style='color: blue;'>"+tr("Cryptosysteme de Playfair")+"</span>");
    label->setFont(QFont("", 26, -1, true));
    label->setAlignment(Qt::AlignCenter);
    auto groupBtn = new QGroupBox(tr("Operation"));
    auto checkBtnEncrypt = new QRadioButton(tr("Cryptage")); checkBtnEncrypt->setChecked(true);
    auto checkBtnDencrypt = new QRadioButton(tr("Décryptage"));
    auto btnEncrypt = new QPushButton(tr("Crypter"));
    groupBtn->setLayout(new QHBoxLayout());
    groupBtn->layout()->addWidget(checkBtnEncrypt);
    groupBtn->layout()->addWidget(checkBtnDencrypt);
    groupBtn->layout()->addWidget(btnEncrypt);
    groupBtn->layout()->setAlignment(Qt::AlignCenter);
    setLayout(new QVBoxLayout());
    layout()->addWidget(label);
    layout()->addWidget(groupBtn);

    //Password
    auto password = new QLineEdit();
    //password->setValidator(QRegularExpressionValidator(QRegularExpression("[A-Z]")));;
    auto layoutPassword = new QHBoxLayout();
    auto widgetPasswordTexte = new QWidget();
    layoutPassword->addWidget(new QLabel(tr("Mot de Passe ")));
    layoutPassword->addWidget(password);
    widgetPasswordTexte->setLayout(layoutPassword);
    layout()->addWidget(widgetPasswordTexte);

    //Text initial, text final
    auto textInit = new QTextEdit();
    auto labelTextInitial = new QLabel(tr("Message claire"));
    auto textFinal = new QTextEdit();
    auto labelTextFinal = new QLabel(tr("Cryptogramme"));
    auto widgetText = new QWidget();
    auto layoutText = new QVBoxLayout();
    layoutText->addWidget(labelTextInitial);
    layoutText->addWidget(textInit);
    layoutText->addWidget(labelTextFinal);
    layoutText->addWidget(textFinal);
    widgetText->setLayout(layoutText);

    //Appercu de password dans un tableau
    auto labelTable = new QLabel("<span style='color: blue;'>"+tr("Apperçu de la table")+"</span>");
    labelTable->setAlignment(Qt::AlignCenter);
    auto layoutGrid = new QGridLayout();
    auto widgetGrid = new QWidget();
    QLineEdit* lsCharacter[5][5];
    for(int i=0; i<5; i++){
        for(int j=0; j< 5; j++){
            lsCharacter[i][j] = new QLineEdit(QString(Playfair::Table[i][j]) + "D");
            lsCharacter[i][j]->setMaxLength(1);
            lsCharacter[i][j]->setMaximumWidth(50);
            lsCharacter[i][j]->setAlignment(Qt::AlignCenter);
            layoutGrid->addWidget(lsCharacter[i][j], i, j);
        }
    }
    widgetGrid->setLayout(layoutGrid);
    auto widgetPasswordGrid = new QWidget();
    widgetPasswordGrid->setLayout(new QVBoxLayout);
    widgetPasswordGrid->layout()->addWidget(labelTable);
    widgetPasswordGrid->layout()->addWidget(widgetGrid);
    widgetPasswordGrid->layout()->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    //SPliter
    auto spliter = new QSplitter();
    spliter->addWidget(widgetText);
    spliter->addWidget(widgetPasswordGrid);

    layout()->addWidget(spliter);

    //Connexion
    //Fonction anonyme
    auto fctCheckButton = [checkBtnEncrypt, checkBtnDencrypt, labelTextInitial, labelTextFinal](bool){
        if(checkBtnEncrypt->isChecked()){
            labelTextInitial->setText(tr("Message claire"));
            labelTextFinal->setText(tr("Cryptogramme"));
        }
        if(checkBtnDencrypt->isChecked()){
            labelTextFinal->setText(tr("Message claire"));
            labelTextInitial->setText(tr("Cryptogramme"));
        }
    };
    auto me = this;
    connect(checkBtnEncrypt, &QRadioButton::toggled, this, fctCheckButton);
    connect(checkBtnDencrypt, &QRadioButton::toggled, this, fctCheckButton);
    connect(btnEncrypt, &QPushButton::clicked, this, [me, textInit, textFinal, password, checkBtnEncrypt, lsCharacter](){
        if(textInit->toPlainText().isEmpty())
            return;
        else
        {
            if(password->text().isEmpty()){
                QMessageBox::information(me, "", tr("Entrez dabord le mot de passe svp"));
                return;
            }else{
                Playfair::setPassword(Playfair::Table, password->text().toUpper().toStdString());
                for(int i=0; i< 5; i++){
                    for(int j=0; j< 5; j++){
                        lsCharacter[i][j]->setText(QString(Playfair::Table[i][j]));
                    }
                }
            }
            if(checkBtnEncrypt->isChecked()){
                textFinal->setText(Playfair::encrypt(textInit->toPlainText().toStdString(), Playfair::Table).c_str());
            }else{
                textFinal->setText(Playfair::deCrypt(textInit->toPlainText().toStdString(), Playfair::Table).c_str());
            }
       }
    });
}

PlayfairWidget::~PlayfairWidget()
{
}

