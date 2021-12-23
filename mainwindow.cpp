#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "string"
#include "consistency.h"
#include "QMessageBox"
#include "xmltojson.h"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "compression.h"
#include "minify.h"
#include "prettyxml.h"

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
        ui->output->setPlainText("False\n");
        ui->output->setPlainText("To correct the error please press the Correct Error button below");
    }

}


void MainWindow::on_beautifyButton_clicked()
{
    qs = ui->input->toPlainText(); //bta5od el kalam mn el text edit
    string temp = qs.toStdString(); //
    temp = minify(&temp);
    prettyxml(&temp);
    QString out = QString::fromStdString(temp);
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
    qs = ui->input->toPlainText(); //bta5od el kalam mn el text edit
    string temp = qs.toStdString(); //
    string minified = minify(&temp);
    string compressed = compress(&minified);
    //string decompressed = decompress(&compressed);
    //prettyxml(&decompressed);
    string count = to_string(compressed.length());
    ui -> output -> setPlainText(QString::fromStdString(count));
}


void MainWindow::on_actionNew_triggered()
{
    file_path="";
    ui->input->setPlainText("");
}


void MainWindow::on_actionOpen_triggered()
{
    QString file_name=QFileDialog::getOpenFileName(this,"open the file");
       QFile file(file_name);
       file_path=file_name;
       if(!file.open(QFile::ReadOnly | QFile::Text)){
           QMessageBox::warning(this,"...","file not open");
           return;

       }
       QTextStream in(&file);
       QString text=in.readAll();
       ui->input->setPlainText(text);
       file.close();
}


void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path);
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this,"...","file not open");
            return;

        }
        QTextStream out(&file);
        QString text=ui->input->toPlainText();
        out << text;
        file.flush();
        file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString file_name=QFileDialog::getSaveFileName(this,"open the file");
        QFile file(file_name);
        file_path=file_name;
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this,"...","file not open");
            return;

        }
        QTextStream out(&file);
        QString text=ui->input->toPlainText();
        out << text;
        file.flush();
        file.close();
}


void MainWindow::on_actionCut_triggered()
{
 ui->input->cut();
}


void MainWindow::on_actionCopy_triggered()
{

    ui->input->copy();
}


void MainWindow::on_actionPaste_triggered()
{
ui->input->paste();
}


void MainWindow::on_actionRedo_triggered()
{
ui->input->redo();
}


void MainWindow::on_actionUndo_triggered()
{
ui->input->undo();
}


void MainWindow::on_minifyButton_clicked()
{

}


void MainWindow::on_correctButton_clicked()
{

}


void MainWindow::on_decompressButton_clicked()
{

}

