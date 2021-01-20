#include "insertclient.h"
#include "ui_insertclient.h"

InsertClient::InsertClient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InsertClient)
{
    ui->setupUi(this);
}

void InsertClient::clear_all_fields()
{
    ui->le_firstname->setText("");
    ui->le_lastname->setText("");
    ui->le_diagnosis->setText("");
}

InsertClient::~InsertClient()
{
    delete ui;
}

void InsertClient::on_pushButton_clicked()
{
    QString firstName = ui->le_firstname->text();
    QString lastName =  ui->le_lastname->text();
    QString sex = ui->cb_sex->currentText();
    QDate birth = ui->de_birthdate->date();
    QString diagnosis = ui->le_diagnosis->text();
    QString birthDate = date_to_postgre(birth);
    QSqlQuery* query = new QSqlQuery(config::db);
    QString query_string = "select \"AddNewClient\"('";
    query_string += firstName + "','";
    query_string += lastName + "',";
    query_string += birthDate + ",'";
    query_string += sex + "','";
    query_string += diagnosis + "')";
    query->exec(query_string);
    qDebug() << query_string;
    qDebug() << query->lastError().text();
    this->hide();
}

void InsertClient::on_pushButton_cancel_clicked()
{
    close();
}
