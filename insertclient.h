#ifndef INSERTCLIENT_H
#define INSERTCLIENT_H

#include <QWidget>
#include "customform.h"
#include <QSqlQuery>
#include <QDebug>

namespace Ui {
class InsertClient;
}

class InsertClient : public QWidget
{
    Q_OBJECT

public:
    explicit InsertClient(QWidget *parent = nullptr);
    void clear_all_fields();
    ~InsertClient();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_cancel_clicked();

private:
    Ui::InsertClient *ui;
};

#endif // INSERTCLIENT_H
