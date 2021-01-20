#include "customform.h"
#include "ui_customform.h"

customForm::customForm( QWidget *parent) :
    QWidget(parent),
    ui(new Ui::customForm)
{
//    ui->setupUi(this);
//    this->client_model = new QSqlTableModel(this, config::db);
//    this->client_model->setTable("Clients");
//    //this->client_model->setQuery("select * from \"ClientsView\"");
//    client_model->select();
//    ui->table_clients->setModel(this->client_model);
//    this->db = QSqlDatabase::addDatabase("QPSQL");
//    this->db.setHostName("127.0.0.1");
//    this->db.setDatabaseName("Optic");
//    this->db.setUserName(config::user_name);
//    this->db.setPassword(config::user_password);
//    if (!config::db.open())
//    {
//        QMessageBox::warning(this, "Attention", config::db.lastError().text());
//        return;
//    }
//    QSqlQueryModel *model = new QSqlQueryModel(this);
//    model->setQuery("select * from \"Persons\"", this->db);
//    ui->table_clients->setModel(model);
//    QSqlQueryModel * model = new QSqlQueryModel;
//    model->setQuery("select * from \"ClientsInfo\"()");
//    ui->table_clients->setModel(model);

}

customForm::~customForm()
{
    delete ui;
}


QString date_to_postgre(QDate date)
{
    //'pppp-mm-dd'
    QString date_string = "";
    int start_year = date.year();
    int start_month = date.month();
    int start_day = date.day();
    date_string += "'" + QString::number(start_year) + "-" + QString::number(start_month) + "-" + QString::number(start_day) + "'";
    return date_string;
}
