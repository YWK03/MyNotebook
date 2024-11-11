#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"aboutdialog.h"
#include"searchdialog.h"
#include"replacepdialog.h"
#include<QFileDialog>
#include<qmessagebox.h>
#include<QTextStream>
#include<QColordialog>
#include<QFontDialog>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textChanged = false;

    on_actionNew_triggered();


    statusLabel.setMaximumWidth(200);
    statusLabel.setText("length:" + QString::number(0) + "   lines:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);


    statusCursorLabel.setMaximumWidth(200);
    statusCursorLabel.setText("Ln:" + QString::number(0) + "   Col:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("杨文铿"));
    ui->statusbar->addPermanentWidget(author);

    ui->actionCopy->setEnabled(false);
    ui->actionRestoration->setEnabled(false);
    ui->actionReplacement->setEnabled(true);
    ui->actionCut->setEnabled(false);
    ui->actionSticking->setEnabled(false);


    QPlainTextEdit::LineWrapMode mode = ui->TextEdit->lineWrapMode();

    if (mode == QTextEdit::NoWrap) {
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actionWrap->setChecked(false);
    } else {
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionWrap->setChecked(true);
    }

    ui->actionToolbar->setChecked(true);
    ui->actionStatusBar->setChecked(true);
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
    SearchDialog dlg(this, ui->TextEdit);
    dlg.exec();
}


void MainWindow::on_actionReplacement_triggered()
{
    ReplacepDialog dlg(this, ui->TextEdit);
    dlg.exec();
}


void MainWindow::on_actionNew_triggered()
{
    if (!useEditConfirmed())
        return;

    filePath = "";


    ui->TextEdit->clear();
    this->setWindowTitle(tr("新建文本文件-编辑器"));
    textChanged = false;
}


void MainWindow::on_actionOpen_triggered()
{
    if (!useEditConfirmed())
        return;


    QString filename = QFileDialog::getOpenFileName(this, "打开文件", ".", tr("Text file(*.txt);;All(*.*)"));
    QFile file(filename);

    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, "..", "打开文件失败");
        return;
    }

    filePath = filename;

    QTextStream in(&file);
    QString text = in.readAll();
    ui->TextEdit->insertPlainText(text);
    file.close();


    this->setWindowTitle(QFileInfo(filename).absoluteFilePath());
    textChanged = false;
}


void MainWindow::on_actionSave_triggered()
{
    if (filePath == "") {

        QString filename = QFileDialog::getSaveFileName(this, "保存文件", ".", tr("Text file(*.txt);;All(*.*)"));
        QFile file(filename);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "..", "打开文件失败");
            return;
        }
        file.close();
        filePath = filename;
    }
    QFile file(filePath);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "打开文件失败");
        return;
    }
    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();
    out << text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
}




void MainWindow::on_actionSaveAnther_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "保存文件", ".", tr("Text file(*.txt);;All(*.*)"));

    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "打开文件失败");
        return;
    }

    filePath = filename;
    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();
    out << text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
    textChanged = false;
}


void MainWindow::on_TextEdit_textChanged()
{
    if (!textChanged) {
        this->setWindowIconText("*" + this->windowTitle());
        textChanged = true;
    }

    statusLabel.setText("length:" + QString::number(ui->TextEdit->toPlainText().length())
                        + "   lines:" + QString::number(ui->TextEdit->document()->lineCount()));

}

bool MainWindow::useEditConfirmed()
{
    QString path = (filePath != "") ? filePath : "无标题.txt";

    if (textChanged) {
        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("...");
        msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("是否将更改保存到\n") + "\"" + path + "\"?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        int r = msg.exec();
        switch (r) {
        case QMessageBox::Yes:
            on_actionSave_triggered();
            break;
        case QMessageBox::No:
            textChanged = false;
            break;
        case QMessageBox::Cancel:
            return false;

        }
    }
    return true;
}


void MainWindow::on_actionCut_triggered()
{
    ui->TextEdit->cut();
    ui->actionSticking->setEnabled(true);
}


void MainWindow::on_actionRevocation_triggered()
{
    ui->TextEdit->undo();
}


void MainWindow::on_actionCopy_triggered()
{
    ui->TextEdit->copy();
    ui->actionSticking->setEnabled(true);
}


void MainWindow::on_actionSticking_triggered()
{
    ui->TextEdit->paste();
}


void MainWindow::on_actionRestoration_triggered()
{
    ui->TextEdit->redo();
}


void MainWindow::on_TextEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
}


void MainWindow::on_TextEdit_redoAvailable(bool b)
{
    ui->actionRestoration->setEnabled(b);
}


void MainWindow::on_TextEdit_undoAvailable(bool b)
{
    ui->actionRevocation->setEnabled(b);
}


void MainWindow::on_actionColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择颜色");
    if (color.isValid()) {
        ui->TextEdit->setStyleSheet(QString("QPlainTextEdit {color：%1}").arg(color.name()));
    }
}


void MainWindow::on_actionEditorBackgroundColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择颜色");
    if (color.isValid()) {
        ui->TextEdit->setStyleSheet(QString("QPlainTextEdit {background-color：%1}").arg(color.name()));
    }

}


void MainWindow::on_actionBackgroundColor_triggered()
{

}


void MainWindow::on_actionWrap_triggered()
{
    QPlainTextEdit::LineWrapMode mode = ui->TextEdit->lineWrapMode();

    if (mode == QTextEdit::NoWrap) {
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actionWrap->setChecked(true);
    } else {
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionWrap->setChecked(false);
    }

}


void MainWindow::on_actionFont_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, this);

    if (ok) {
        ui->TextEdit->setFont(font);
    }
}


void MainWindow::on_actionToolbar_triggered()
{
    bool visible = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visible);
    ui->actionToolbar->setChecked(!visible);
}


void MainWindow::on_actionStatusBar_triggered()
{
    bool visible = ui->statusbar->isVisible();
    ui->statusbar->setVisible(!visible);
    ui->actionStatusBar->setChecked(!visible);
}


void MainWindow::on_action_A_triggered()
{
    ui->TextEdit->selectAll();
}


void MainWindow::on_actionOut_triggered()
{
    if (useEditConfirmed()) {
        exit(0);
    }
}

void MainWindow::on_TextEdit_cursorPositionChanged()
{
    int col = 0;
    int ln = 0;
    int flg = -1;
    int pos = ui->TextEdit->textCursor().position();
    QString text = ui->TextEdit->toPlainText();

    for (int i = 0; i < pos; i++) {
        if (text[i] == '\n') {
            ln++;
            flg = i;
        }
    }
    flg++;
    col = pos - flg;
    statusCursorLabel.setText("Ln:" + QString::number(ln + 1) + "   Col:" +
                              QString::number(col + 1));
}

