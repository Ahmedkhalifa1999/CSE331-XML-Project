#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "string"
#include "consistency.h"
#include "QMessageBox"
#include "QFile"
#include "QFileDialog"
#include "QMessageBox"
#include "compression.h"
#include "prettyxml.h"
#include "XMLtoJSON/xmltojson.h"
#include <fstream>

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

void MainWindow::on_checkError_clicked()
{
    string input = ui->input->toPlainText().toStdString();
    if(detection(input) == true){
        ui->output->setPlainText("True");
    }
    else{
        ui->output->setPlainText("False\n");
        ui->output->setPlainText("To correct the error please press the Correct Error button below");
    }

}


void MainWindow::on_beautifyButton_clicked()
{
    string input = ui->input->toPlainText().toStdString();
    input = minify(&input);
    prettyxml(&input);
    QString output = QString::fromStdString(input);
    ui->output->setPlainText(output);
}

void MainWindow::on_convertButton_clicked() {

    string input = ui->input->toPlainText().toStdString();
    string minified = minify(&input);
    prettyxml(&minified);
    string json = xmltojson(&minified);
    QString output = QString::fromStdString(json);
    ui->output->setPlainText(output);
}

void MainWindow::on_compressButton_clicked()
{

    /*
    //Works correctly, decompression still doesn't work correctly (problems with reading file)
    string input = ui->input->toPlainText().toStdString();
    input = minify(&input);
    string compressed = compress(&input);
    QString output = QString::fromStdString(compressed);
    QString file_name = QFileDialog::getSaveFileName(this,"open the file");
        QFile file(file_name);
        file_path=file_name;
        if(!file.open(QFile::WriteOnly | QFile::Text)){
            QMessageBox::warning(this,"...","file not open");
            return;

        }
    std::ofstream out(file_name.toStdString());
    out << compressed;
    file.flush();
    file.close();
    */


    string input = ui->input->toPlainText().toStdString();
    string minified = minify(&input);
    string compressed = compress(&minified);
    string decompressed = decompress(&compressed);
    prettyxml(&decompressed);
    QString output = QString::fromStdString(decompressed);
    ui->output->setPlainText(output);

}

void MainWindow::on_minifyButton_clicked()
{
    string input = ui->input->toPlainText().toStdString();
    QString output = QString::fromStdString(minify(&input));
    ui->output->setPlainText(output);
}


void MainWindow::on_correctButton_clicked()
{
    string input = ui->input->toPlainText().toStdString();
    QString output = QString::fromStdString(correction(input));
    ui->output->setPlainText(output);
}


void MainWindow::on_decompressButton_clicked()
{
    /*
    //fstream reaches end of file prematurely
    QString file_name=QFileDialog::getOpenFileName(this,"open the file");
       QFile file(file_name);
       file_path=file_name;
       if(!file.open(QFile::ReadOnly | QFile::Text)){
           QMessageBox::warning(this,"...","file not open");
           return;

       }
    //QTextStream in(&file);
    std::ifstream in(file_name.toStdString());
    //int length = in.gcount();
    //char inputArray[length+1];
    //in.get(inputArray, length);
    //inputArray[length] = 0;
    //std::stringstream buffer;
    //buffer << in.rdbuf();
    //std::string input(std::istreambuf_iterator<char>{in}, {});
    //string input = buffer.str();

    string input;
    char current;
    in >> current;
    while(!in.eof()) {
        input.push_back(current);
        in >> current;
    }
    QString output = QString::fromStdString(decompress(&input));
    ui->output->setPlainText(output);
    file.close();
    */
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

