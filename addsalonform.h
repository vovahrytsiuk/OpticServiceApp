#ifndef ADDSALONFORM_H
#define ADDSALONFORM_H

#include <QWidget>
#include "customform.h"


namespace Ui {
class AddSalonForm;
}

class AddSalonForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddSalonForm(QWidget *parent = nullptr);
    ~AddSalonForm();
    void clear_all_fields();

private slots:
    void on_salon_cancel_button_clicked();

    void on_salon_add_buton_clicked();

private:
    Ui::AddSalonForm *ui;
};

#endif // ADDSALONFORM_H
