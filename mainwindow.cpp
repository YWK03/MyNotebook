#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"aboutdialog.h"
#include"searchdialog.h".h"
#include"replacepdialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    statusLabel.setMaximumWidth(150);
    statusLabel.setText("length:" + QString::number(0) + "   lines:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);


    statusCursorLabel.setMaximumWidth(150);
    statusCursorLabel.setText("Ln:" + QString::number(0) + "   Col:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("杨文铿"));
    ui->statusbar->addPermanentWidget(author);
}

MainWindow::~MainWindow()
{
    delete ui;


}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionLooking_triggered()
{
    SearchDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionReplacement_triggered()
{
    ReplacepDialog dlg;
    dlg.exec();
}

