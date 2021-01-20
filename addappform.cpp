#include "addappform.h"
#include "ui_addappform.h"

AddAppForm::AddAppForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddAppForm)
{
    ui->setupUi(this);
    this->mapper_client = new QDataWidgetMapper(this);
    this->mapper_doctor = new QDataWidgetMapper(this);
    this->mapper_salon = new QDataWidgetMapper(this);

}

AddAppForm::~AddAppForm()
{
    delete ui;
}

void AddAppForm::setClientModel(QAbstractItemModel *mod)
{
    this->mapper_client->setModel(mod);
    this->mapper_client->addMapping(ui->client_first_name, 1);
    this->mapper_client->addMapping(ui->client_last_name, 2);
    this->mapper_client->addMapping(ui->client_id, 0);
}

void AddAppForm::setDoctorModel(QAbstractItemModel *mod)
{
    this->mapper_doctor->setModel(mod);
    this->mapper_doctor->addMapping(ui->doctor_first_name, 1);
    this->mapper_doctor->addMapping(ui->doctor_last_name, 2);
    this->mapper_doctor->addMapping(ui->doctor_id, 0);
}

void AddAppForm::setSalonModel(QAbstractItemModel *mod)
{
    this->mapper_salon->setModel(mod);
    this->mapper_salon->addMapping(ui->salon_name, 1);
    this->mapper_salon->addMapping(ui->salon_id, 0);
}

void AddAppForm::on_pushButton_2_clicked()
{
    close();
}

void AddAppForm::on_pushButton_clicked()
{
    QSqlQuery query(config::db);
    QString clientid = ui->client_id->text();
    QString doctorid = ui->doctor_id->text();
    QString salonid = ui->salon_id->text();
    QString date = date_to_postgre(ui->dateEdit->date());
    QString desc  = ui->description->text();
    if(clientid != "" && doctorid != "" && salonid != "")
    {
        QString query_line = "insert into \"Appointments\"(\"ClientID\", \"DoctorID\", \"SalonID\", \"Date\", \"Description\") values(";
        query_line += clientid + "," + doctorid + ", " + salonid + ", " + date  + ",'" + desc +"')";
        qDebug() << query_line;
        if(!query.exec(query_line))
        {
            QMessageBox::warning(this, "Attention", query.lastError().text());
        }
        close();
    }
}
