#ifndef DOCTOREDITFORM_H
#define DOCTOREDITFORM_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "customform.h"
#include <iostream>


namespace Ui {
class DoctorEditForm;
}

class DoctorEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit DoctorEditForm(QWidget *parent = nullptr);
    ~DoctorEditForm();
    QDataWidgetMapper* mapper;
    void setModel(QAbstractItemModel* mod);

private slots:
    void on_update_button_clicked();

    void on_delete_button_clicked();

    void on_cancell_button_clicked();

private:
    Ui::DoctorEditForm *ui;
    QString generate_update_query();
    QString generate_delete_query();
    int read_client_id();

};

#endif // DOCTOREDITFORM_H
