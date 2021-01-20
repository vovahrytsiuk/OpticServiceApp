#ifndef CLIENTEDITFORM_H
#define CLIENTEDITFORM_H

#include <QWidget>
#include <QDataWidgetMapper>
#include "customform.h"
#include <QDebug>


namespace Ui {
class ClientEditForm;
}

class ClientEditForm : public QWidget
{
    Q_OBJECT

public:
    explicit ClientEditForm(QWidget *parent = nullptr);
    ~ClientEditForm();
    QDataWidgetMapper* mapper;
    void setModel(QAbstractItemModel * mod);

private slots:
    void on_cancell_button_clicked();

    void on_update_button_clicked();

    void on_delete_button_clicked();

private:
    Ui::ClientEditForm *ui;
    int current_client_id;
    int read_client_id();
    QString generate_query_update();
    QString generate_query_delete();


};

#endif // CLIENTEDITFORM_H
