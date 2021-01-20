#ifndef ADDDOCTORFORM_H
#define ADDDOCTORFORM_H

#include <QWidget>
#include "customform.h"

namespace Ui {
class AddDoctorForm;
}

class AddDoctorForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddDoctorForm(QWidget *parent = nullptr);
    ~AddDoctorForm();
    void clear_all_fields();

private slots:
    void on_add_doctor_button_clicked();

    void on_doctor_cancel_clicked();

private:
    Ui::AddDoctorForm *ui;
};

#endif // ADDDOCTORFORM_H
