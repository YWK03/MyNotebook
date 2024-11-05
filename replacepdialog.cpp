#include "replacepdialog.h"
#include "ui_replacepdialog.h"

ReplacepDialog::ReplacepDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ReplacepDialog)
{
    ui->setupUi(this);
}

ReplacepDialog::~ReplacepDialog()
{
    delete ui;
}
