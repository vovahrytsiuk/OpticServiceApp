#ifndef SALONEDITFORM_H
#define SALONEDITFORM_H

#include <QWidget>
#include "customform.h"
#include <QDataWidgetMapper>

namespace Ui {
class SalonEditForm;
}

class SalonEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit SalonEditForm(QWidget *parent = nullptr);
    ~SalonEditForm();
    QDataWidgetMapper* mapper;
    void setModel(QAbstractItemModel* mod);

private slots:
    void on_salon_update_button_clicked();

    void on_salon_cancel_button_clicked();

    void on_salon_delete_button_clicked();

private:
    Ui::SalonEditForm *ui;
    QString generate_update_query();
    QString generate_delete_query();
    int read_salon_id();
};

#endif // SALONEDITFORM_H
