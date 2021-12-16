#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "string"
#include "consist.h"
#include "QMessageBox"
#include "xmltojson.h"


void prettifying(string* text);

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString qs;
string in;

void MainWindow::on_checkError_clicked()
{
    qs = ui->input->toPlainText(); //bta5od el kalam mn el text edit
    in = qs.toStdString(); //
    bool flag = true;
    flag = detection(in);
    if(flag == true){
        ui->output->setPlainText("True");
    }
    else{
        ui->output->setPlainText("False");
    }

}


void MainWindow::on_beautifyButton_clicked()
{
    qs = ui->input->toPlainText(); //bta5od el kalam mn el text edit
    string temp = qs.toStdString(); //
    QString out = QString::fromUtf8(temp);
    ui->output->setPlainText(out);
    prettifying(&temp);
    out = QString::fromUtf8(temp);
    ui->output->setPlainText(out);
}

void MainWindow::on_convertButton_clicked() {
    qs = ui->input->toPlainText(); //bta5od el kalam mn el text edit
    string in = qs.toStdString(); //
    string out = convert(&in);
    ui->output->setPlainText(QString::fromStdString(out));
}

void MainWindow::on_compressButton_clicked()
{

}

