#include "adfgvxWidget.h"

AdfgvxWidget::AdfgvxWidget(QWidget *parent)
    : QMainWindow(parent)
{
    auto title = new QLabel("<span style='color: blue'>"+tr("Cryptosysteme ADFGVX")+"</span>");
    QLabel* labelTextInit = new QLabel("Texte claire"),
            *labelTexteFinale = new QLabel(tr("Cryptogramme"));
    title->setAlignment(Qt::AlignHCenter);
    title->setFont(QFont("", 35, -1, true));
    auto groupeBox = new QGroupBox(tr("Operation"));
    groupeBox->setAlignment(Qt::AlignCenter);
    auto btnRandomisePassword = new QPushButton(tr("Randomizer"));
    auto btnEncrypt = new QRadioButton(tr("Cryptage")); btnEncrypt->setChecked(true);
    auto btnDecrypt = new QRadioButton(tr("Décryptage"));
    auto textInit = new QTextEdit();
    auto textFinal = new QTextEdit();
    auto btnSubmit = new QPushButton("Crypter");
    auto spliter = new QSplitter();
    auto wRigth = new QWidget();
    auto wLeft = new QWidget();


    QLineEdit *lsGrid[7][7]; auto layoutGrid = new QGridLayout();
    QString ADFGVX = "ADFGVX";
    for(int i=1; i< 7; i++){
        lsGrid[i][0] = new QLineEdit(QString(ADFGVX[i-1])); lsGrid[i][0]->setStyleSheet("color: blue;");
        lsGrid[i][0]->setMaxLength(1); lsGrid[i][0]->setAlignment(Qt::AlignCenter);
        lsGrid[0][i] = new QLineEdit(QString(ADFGVX[i-1]));
        lsGrid[0][i]->setMaxLength(1); lsGrid[0][i]->setAlignment(Qt::AlignCenter);
        lsGrid[0][i]->setStyleSheet("color: blue;");
        lsGrid[0][i]->setReadOnly(true);
        lsGrid[i][0]->setReadOnly(true);

        layoutGrid->addWidget(lsGrid[0][i], 0, i);
        layoutGrid->addWidget(lsGrid[i][0], i, 0);
        for(int j=1; j< 7; j++){
            lsGrid[i][j] = new QLineEdit(QString(Adfgvx::Table[i-1][j-1]));
            lsGrid[i][j]->setMaxLength(1);
            lsGrid[i][j]->setAlignment(Qt::AlignCenter);
            //lsGrid[i][j]->setMaximumSize(45, 45);
            layoutGrid->addWidget(lsGrid[i][j], i, j);
        }
    }

    btnRandomisePassword->setToolTip(tr("Cliquez pour obtenir une clé de façons aleatoir"));

    groupeBox->setLayout(new QHBoxLayout());
    groupeBox->layout()->addWidget(btnEncrypt);
    groupeBox->layout()->addWidget(btnDecrypt);
    groupeBox->layout()->addWidget(btnSubmit);
    groupeBox->layout()->setAlignment(Qt::AlignCenter);
    auto lF = new QFormLayout();
    //lF->addWidget(title);
    lF->addWidget(groupeBox);
    lF->addRow(labelTextInit);
    lF->addWidget(textInit);
    lF->addWidget(labelTexteFinale);
    lF->addWidget(textFinal);
    lF->setAlignment(btnSubmit, Qt::AlignCenter);

    auto wGrid = new QWidget();
    wGrid->setLayout(layoutGrid);
    wLeft->setLayout(lF);
    wRigth->setLayout(new QVBoxLayout());
    auto labelKey = new QLabel("<span style='color: blue'>"+tr("Clef de (dé)chiffrement")+"</span>");
    labelKey->setAlignment(Qt::AlignCenter);
    labelKey->setFont(QFont("", 16, -1, true));
    wRigth->layout()->addWidget(labelKey);
    wRigth->layout()->addWidget(wGrid);
    wRigth->layout()->addWidget(btnRandomisePassword);
    wRigth->layout()->setAlignment(btnRandomisePassword, Qt::AlignCenter | Qt::AlignTop);
    wRigth->layout()->setAlignment(labelKey, Qt::AlignCenter | Qt::AlignTop);
    wRigth->layout()->setAlignment(wGrid, Qt::AlignCenter);

    spliter->addWidget(wLeft);
    spliter->addWidget(wRigth);
    setCentralWidget(new QWidget());
    centralWidget()->setLayout(new QVBoxLayout());
    centralWidget()->layout()->addWidget(title);
    centralWidget()->layout()->setAlignment(title, Qt::AlignCenter);
    centralWidget()->layout()->addWidget(spliter);

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
    connect(btnSubmit, &QPushButton::clicked, this, [me, textInit, textFinal, btnEncrypt, lsGrid](){
        if(textInit->toPlainText().isEmpty()) return ;
        for(int i=1; i< 7; i++){
            for(int j=1; j< 7; j++){
                if(lsGrid[i][j]->text().isEmpty()){
                    QMessageBox::information(me, "", tr("Certaines cases du tableau sont vides veuillez les remplir svp"));
                    return ;
                }
                Adfgvx::Table[i-1][j-1] = lsGrid[i][j]->text().at(0).toLatin1();
            }
        }
        if(btnEncrypt->isChecked()){
            auto txt = Adfgvx::encrypt(textInit->toPlainText().toStdString());
            textFinal->setText(txt.c_str());
        }else{
            auto txt = Adfgvx::deCrypt(textInit->toPlainText().toStdString());
            textFinal->setText(txt.c_str());
        }
    });
    connect(btnRandomisePassword, &QPushButton::clicked, this, [lsGrid](){
        auto key = Adfgvx::randomiseAdfgvxTab();
        int index=0;
        for(int i=1; i< 7; i++){
            for(int j=1; j< 7; j++){
                Adfgvx::Table[i-1][j-1] = key[index];
                lsGrid[i][j]->setText(QString(key[index++]));
            }
        }
    });
}

AdfgvxWidget::~AdfgvxWidget()
{
}

