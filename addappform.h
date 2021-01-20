#ifndef ADDAPPFORM_H
#define ADDAPPFORM_H

#include <QWidget>
#include "customform.h"
#include <QDataWidgetMapper>

namespace Ui {
class AddAppForm;
}

class AddAppForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddAppForm(QWidget *parent = nullptr);
    ~AddAppForm();

    QDataWidgetMapper* mapper_client;
    QDataWidgetMapper* mapper_doctor;
    QDataWidgetMapper* mapper_salon;
    void setClientModel(QAbstractItemModel * mod);
    void setDoctorModel(QAbstractItemModel * mod);
    void setSalonModel(QAbstractItemModel * mod);


private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::AddAppForm *ui;
};

#endif // ADDAPPFORM_H
