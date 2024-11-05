#ifndef REPLACEPDIALOG_H
#define REPLACEPDIALOG_H

#include <QDialog>

namespace Ui {
class ReplacepDialog;
}

class ReplacepDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReplacepDialog(QWidget *parent = nullptr);
    ~ReplacepDialog();

private:
    Ui::ReplacepDialog *ui;
};

#endif // REPLACEPDIALOG_H
