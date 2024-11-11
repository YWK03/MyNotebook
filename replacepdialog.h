#ifndef REPLACEPDIALOG_H
#define REPLACEPDIALOG_H

#include <QDialog>
#include<QPlainTextEdit>

namespace Ui {
class ReplacepDialog;
}

class ReplacepDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplacepDialog(QWidget *parent = nullptr, QPlainTextEdit* textEdit = nullptr);
    ~ReplacepDialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::ReplacepDialog *ui;
    QPlainTextEdit *pTextEdit;
};

#endif // REPLACEPDIALOG_H
