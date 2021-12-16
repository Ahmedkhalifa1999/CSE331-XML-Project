#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QFileDialog"
#include "QTextStream"
#include"QMessageBox"
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->plainTextEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionNew_triggered()
{
   file_path="";
   ui->plainTextEdit->setPlainText("");
}


void MainWindow::on_actionOpen_triggered()
{
   QString file_name=QFileDialog::getOpenFileName(this,"open the file");
   QFile file(file_name);
   file_path=file_name;
   if(!file.open(QFile::ReadOnly) | (QFile::Text)){
       QMessageBox::warning(this,"...","file not open");
       return;

   }
   QTextStream in(&file);
   QString text=in.readAll();
   ui->plainTextEdit->setPlainText(text);
   file.close();
}


void MainWindow::on_actionSave_triggered()
{

    QFile file(file_path);
    if(!file.open(QFile::WriteOnly) | (QFile::Text)){
        QMessageBox::warning(this,"...","file not open");
        return;

    }
    QTextStream out(&file);
    QString text=ui->plainTextEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionSave_as_triggered()
{
    QString file_name=QFileDialog::getSaveFileName(this,"open the file");
    QFile file(file_name);
    file_path=file_name;
    if(!file.open(QFile::WriteOnly) |(QFile::Text)){
        QMessageBox::warning(this,"...","file not open");
        return;

    }
    QTextStream out(&file);
    QString text=ui->plainTextEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}


void MainWindow::on_actionCut_triggered()
{
    ui->plainTextEdit->cut();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->plainTextEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->plainTextEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->plainTextEdit->redo();
}


void MainWindow::on_actionUndo_triggered()
{
    ui->plainTextEdit->undo();
}



void MainWindow::on_checkError_clicked()
{

}


void MainWindow::on_formatButton_clicked()
{

}


void MainWindow::on_convertButton_clicked()
{

}


void MainWindow::on_compressButton_clicked()
{

}

