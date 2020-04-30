#include "include/mainwindow.h"
#include "ui_mainwindow.h"
#include "../include/DeBruijnGraph.h"

#include <string>
#include <vector>
#include <QMessageBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_origstr_btn_clicked()
{
    vector<string> Reads;
    int k = ui->k_inp->value();

    if (ui->reads_in->toPlainText().isEmpty() || ui->reads_in->toPlainText().isNull())
    {
        QMessageBox msg;
        msg.setText("Please enter the reads.");
        msg.setWindowTitle("Input Error");
        msg.exec();
        return;
    }

    QString reads_input = ui->reads_in->toPlainText();

    // Purify the input by chopping off \n or spaces or non-printable characters
    while (reads_input.back().isSpace() || reads_input.back() == '\n' || !reads_input.back().isPrint())
    {
        reads_input.chop(1);
    }

    QStringList reads_list = reads_input.split('\n');

    if (reads_list.isEmpty() || k < 2)
    {
        QMessageBox msg;
        msg.setText("Value of K should be atleast 2, and number of reads should be more than 0.");
        msg.setWindowTitle("Input Error");
        msg.exec();
        return;
    }

    for (auto it = reads_list.begin(); it != reads_list.end(); it++)
    {
        Reads.push_back((*it).toStdString());
    }

    KMerifier kmf = KMerifier(k, Reads);

    DeBruijnGraph dbg = DeBruijnGraph(kmf);

    string original = dbg.DoEulerianWalk();

    ui->origstr_out->setPlainText(QString(original.c_str()));
}
