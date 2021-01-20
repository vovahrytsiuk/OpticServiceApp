#ifndef CUSTOMFORM_H
#define CUSTOMFORM_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QDate>
#include <QSqlQuery>
#include <QDebug>




QT_BEGIN_NAMESPACE
namespace config {
static QString user_name;
static QString user_password;
static QSqlDatabase db;
}
QT_END_NAMESPACE


QString date_to_postgre(QDate date);

namespace Ui {
class customForm;
}

class customForm : public QWidget
{
    Q_OBJECT

public:
    explicit customForm( QWidget *parent = nullptr);
    ~customForm();

private:
    Ui::customForm *ui;
    QSqlTableModel *client_model;
    QSqlDatabase db;
};

#endif // CUSTOMFORM_H
