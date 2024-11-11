#include "replacepdialog.h"
#include "ui_replacepdialog.h"
#include<QMessageBox>
ReplacepDialog::ReplacepDialog(QWidget *parent, QPlainTextEdit* textEdit)
    : QDialog(parent)
    , ui(new Ui::ReplacepDialog)
{
    ui->setupUi(this);
    pTextEdit = textEdit;

    ui->radioButton_2->setChecked(true);
}

ReplacepDialog::~ReplacepDialog()
{
    delete ui;
}

void ReplacepDialog::on_pushButton_clicked()
{
    QString target = ui->searchText->text();

    if (target == "" || pTextEdit == nullptr)
        return;

    QString text = pTextEdit->toPlainText();
    QTextCursor c = pTextEdit->textCursor();
    int index = -1;
    if (ui->radioButton_2->isChecked()) {

        index = text.indexOf(target, c.position(), ui->checkBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

        if (index >= 0) {
            c.setPosition(index);
            c.setPosition(index + target.length(), QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }
    } else if (ui->radioButton->isChecked()) {
        index = text.lastIndexOf(target, c.position() - text.length() - 1);
        if (index >= 0) {
            c.setPosition(index + target.length());
            c.setPosition(index, QTextCursor::KeepAnchor);

            pTextEdit->setTextCursor(c);
        }

    }

    if (index < 0) {
        QMessageBox msg(this);
        msg.setWindowTitle("jishiben");
        msg.setText(QString("找不到 ") + target);
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
}


void ReplacepDialog::on_pushButton_2_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->replaceText->text();

    if ((pTextEdit != nullptr) && (target != "") && (to != "")) {
        QString selText = pTextEdit->placeholderText();

        if (selText == target) {
            pTextEdit->insertPlainText(to);
        }
        on_pushButton_clicked();
    }
}


void ReplacepDialog::on_pushButton_3_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->replaceText->text();

    if ((pTextEdit != nullptr) && (target != "") && (to != "")) {
        QString text = pTextEdit->toPlainText();

        text.replace(target, to, ui->checkBox->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

        pTextEdit->clear();

        pTextEdit->insertPlainText(text);
    }
}


void ReplacepDialog::on_pushButton_4_clicked()
{
    accept();
}

