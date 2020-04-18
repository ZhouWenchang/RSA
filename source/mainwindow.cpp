#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QDebug>
using namespace  std;

char c[1024],m2[1024];
CBigInt e = 0x10001;
CBigInt n, d;
int eSize;
string m3;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Generate_Key_Button_clicked(){

    CBigInt p = GeneratePrime(256);
    CBigInt q = GeneratePrime(256);
    n = p * q;
    CBigInt Fn = (p - 1) * (q - 1);
    d = CongruenceEquation(e, Fn);
    CBigInt r = (e * d) % Fn;


    string SPublicKey="";
    string SPrivateKey="";
    e.PutToString(SPublicKey,16);
    d.PutToString(SPrivateKey,16);
    QString QPublicKey=QString::fromStdString(SPublicKey);
    QString QPrivateKey=QString::fromStdString(SPrivateKey);
    ui->PublicKey_Content->setText(QPublicKey);
    ui->PrivateKey_Content->setText(QPrivateKey);
        }

void MainWindow::on_Enctypt_Button_clicked(){
    QString QPlaintext=ui->Plaintext_Content->toPlainText();
    string SPlaintext=QPlaintext.toStdString();


    //Core Encrypt
    const char *m=SPlaintext.data();

    int eSize = Rsa_Pkcs15_Encrypt(e, n, 512, (void *)m, strlen(m), c, 1024);
    string CipherTemp="";
    for (int i = 0; i < eSize; i++) {
            if (c[i] > 0) {
                CipherTemp+=c[i];
            }
        }
    //


    string SCiphertext=CipherTemp;
    QString QCiphertext=QString::fromStdString(SCiphertext);
    ui->Ciphertext_Content->setText(QCiphertext);

    int dSize = Rsa_Pkcs15_Decrypt(d, n, 512, c, eSize, m2, 1024);
    m2[dSize] = '\0';
    m3=m2;
        }
void MainWindow::on_Dectypt_Button_clicked(){
    QString QCiphertext=ui->Ciphertext_Content->toPlainText();
    string SCiphertext=QCiphertext.toStdString();
    //Core Decrypt
    string NewPlainTemp(m3);
    //
    string SNewPlaintext=NewPlainTemp;
    QString QNewPlaintext=QString::fromStdString(SNewPlaintext);
    ui->New_Plaintext_Content->setText(QNewPlaintext);

        }

