#include "cryptoflotwidget.h"

CryptoFlotWidget::CryptoFlotWidget(QWidget *parent)
    : QWidget(parent)
{
    //Entete
    auto label = new QLabel("<span style='color: blue;'>"+tr("Chiffrement par flot(chiffre de Vernam)")+"</span>");
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
    password->setReadOnly(true);

    //Text initial, text final
    auto textInit = new QTextEdit();
    auto labelTextInitial = new QLabel(tr("Message claire"));
    auto textFinal = new QTextEdit();
    auto labelTextFinal = new QLabel(tr("Cryptogramme"));
    auto widgetText = new QWidget();
    auto layoutText = new QFormLayout();
    auto labelTextAscci = new QLabel("<span style='color: blue;'>"+tr("Valeurs ASCII")+"</span>");
    labelTextAscci->setAlignment(Qt::AlignCenter);
    labelTextAscci->setFont(QFont("", 16, -1, true));
    layoutText->addWidget(labelTextAscci);
    layoutText->addRow(tr("CLEF"), password);
    layoutText->addWidget(labelTextInitial);
    layoutText->addWidget(textInit);
    layoutText->addWidget(labelTextFinal);
    layoutText->addWidget(textFinal);
    widgetText->setLayout(layoutText);

    //Appercu sous forme de binaire
    auto labelBinaire = new QLabel("<span style='color: blue;'>"+tr("Valeurs Binaires")+"</span>");
    labelBinaire->setAlignment(Qt::AlignCenter);
    labelBinaire->setFont(labelTextAscci->font());
    auto layoutBinaire = new QFormLayout();
    auto widgetBinaire = new QWidget();
    auto textInitBinair = new QTextEdit(); textInitBinair->setReadOnly(true);
    auto textFinalBinair = new QTextEdit(); textFinalBinair->setReadOnly(true);
    auto passwordBinaire = new QLineEdit(); //passwordBinaire->setReadOnly(true);
    auto labelTextInitBinaire = new QLabel(labelTextInitial->text());
    auto labelTextFinalBinaire = new QLabel(labelTextFinal->text());

    layoutBinaire->addWidget(labelBinaire);
    layoutBinaire->addRow(tr("CLEF"), passwordBinaire);
    layoutBinaire->addWidget(labelTextInitBinaire);
    layoutBinaire->addWidget(textInitBinair);
    layoutBinaire->addWidget(labelTextFinalBinaire);
    layoutBinaire->addWidget(textFinalBinair);
    widgetBinaire->setLayout(layoutBinaire);

    //SPliter
    auto spliter = new QSplitter();
    spliter->addWidget(widgetText);
    spliter->addWidget(widgetBinaire);

    layout()->addWidget(spliter);

    //Connexion
    //Fonction anonyme
    auto fctCheckButton = [btnEncrypt, checkBtnEncrypt, checkBtnDencrypt, labelTextInitial, labelTextInitBinaire, labelTextFinal, labelTextFinalBinaire, password](bool){
        if(checkBtnEncrypt->isChecked()){
            labelTextInitial->setText(tr("Message claire")); labelTextInitBinaire->setText(labelTextInitial->text());
            labelTextFinal->setText(tr("Cryptogramme")); labelTextFinalBinaire->setText(labelTextFinal->text());
            password->setReadOnly(true);
            btnEncrypt->setText(tr("Crypter"));
        }
        if(checkBtnDencrypt->isChecked()){
            labelTextFinal->setText(tr("Message claire")); labelTextFinalBinaire->setText(labelTextFinal->text());
            labelTextInitial->setText(tr("Cryptogramme")); labelTextInitBinaire->setText(labelTextInitial->text());
            password->setReadOnly(false);
            btnEncrypt->setText(tr("Décrypter"));
        }
    };
    //Connexion
    auto me = this;
    connect(checkBtnEncrypt, &QRadioButton::toggled, this, fctCheckButton);
    connect(checkBtnDencrypt, &QRadioButton::toggled, this, fctCheckButton);
    connect(btnEncrypt, &QPushButton::clicked, this, [me, textInit, textFinal, password, checkBtnEncrypt, textFinalBinair](){
        if(textInit->toPlainText().isEmpty())
            return;
        if(checkBtnEncrypt->isChecked()){
            auto result = CryptosystemFlot::encrypt(textInit->toPlainText().toStdString());
            textFinal->setText(result.first.c_str());
            textFinalBinair->setText(CryptosystemFlot::strAsBinairy(result.first.c_str()).c_str());
            password->setText(result.second.c_str());
        }else{
            if(password->text().isEmpty()){
                QMessageBox::warning(me, "", tr("Entrez le mot de passe svp"));
                return;
            }
            auto result = CryptosystemFlot::deccrypt(textInit->toPlainText().toStdString(), password->text().toStdString());
            textFinal->setText(result.c_str());
        }
    });
    connect(textInit, &QTextEdit::textChanged, this, [textInit, textInitBinair](){
       textInitBinair->setText(CryptosystemFlot::strAsBinairy(textInit->toPlainText().toStdString()).c_str());
    });
    connect(password, &QLineEdit::textChanged, this, [password, passwordBinaire](){
       passwordBinaire->setText(CryptosystemFlot::strAsBinairy(password->text().toStdString()).c_str());
    });
}

CryptoFlotWidget::~CryptoFlotWidget()
{
}

