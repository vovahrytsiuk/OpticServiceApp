#include "appeditform.h"
#include "ui_appeditform.h"

AppEditForm::AppEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppEditForm)
{
    ui->setupUi(this);
}

AppEditForm::~AppEditForm()
{
    delete ui;
}
