#ifndef ADDAPPOINMENTINFOFORM_H
#define ADDAPPOINMENTINFOFORM_H

#include <QWidget>
#include "customform.h"
#include <QDataWidgetMapper>

namespace Ui {
class AddAppoinmentInfoForm;
}

class AddAppoinmentInfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddAppoinmentInfoForm(QWidget *parent = nullptr);
    ~AddAppoinmentInfoForm();
    QDataWidgetMapper* mapper;
    void setModel(QAbstractItemModel* mod);
    void fill_table();


private slots:
    void on_close_button_clicked();

private:
    Ui::AddAppoinmentInfoForm *ui;
    QSqlTableModel* model;
};

#endif // ADDAPPOINMENTINFOFORM_H
