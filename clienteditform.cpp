#include "clienteditform.h"
#include "ui_clienteditform.h"

ClientEditForm::ClientEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientEditForm)
{
    ui->setupUi(this);
    this->mapper = new QDataWidgetMapper(this);

}

ClientEditForm::~ClientEditForm()
{
    delete ui;
}


void ClientEditForm::setModel(QAbstractItemModel *mod)
{
    this->mapper->setModel(mod);
    this->mapper->addMapping(ui->client_id_data, 0);
    this->mapper->addMapping(ui->first_name_edit, 1);
    this->mapper->addMapping(ui->last_name_edit, 2);
    this->mapper->addMapping(ui->dateEdit, 3);
    this->mapper->addMapping(ui->sex_edit, 4);
    this->mapper->addMapping(ui->diagnosis_edit, 5);

}

void ClientEditForm::on_cancell_button_clicked()
{
    close();
}



void ClientEditForm::on_update_button_clicked()
{

    QSqlQuery query(config::db);
    QString query_line = this->generate_query_update();
    if(query_line != "")
    {
        query.exec(query_line);
        qDebug() << query.lastError().text();

    }
    else
    {
        qDebug() << "Invalid query line";
    }

    close();
}

int ClientEditForm::read_client_id()
{
    return ui->client_id_data->text().toInt();
}


QString ClientEditForm::generate_query_update()
{
    int current_client_id = this->read_client_id();
    QString new_first_name = ui->first_name_edit->text();
    QString new_last_name = ui->last_name_edit->text();
    QString new_date = date_to_postgre(ui->dateEdit->date());
    QString new_sex = ui->sex_edit->currentText();
    QString new_diagnosis = ui->diagnosis_edit->toPlainText();
    qDebug() << new_diagnosis;

    if(new_first_name != "" && new_last_name != "")
    {
        QString query = "select \"UpdateClient\"(";
        query += QString::number(current_client_id) + ",";
        query += "'" + new_first_name + "'";
        query += " , ";
        query += "'" + new_last_name + "'";
        query += " , ";
        query += new_date;
        query += " , ";
        query += "'" + new_sex + "'";
        query += " , ";
        query += "'" + new_diagnosis + "'";
        query +=")";
        qDebug() << query;
        return query;
    }
    return "";


}

QString ClientEditForm::generate_query_delete()
{
    int current_client_id = this->read_client_id();
    QString query = " delete from \"Persons\" where \"PersonID\"  = (select \"PersonID\" from \"Clients\" where \"ClientID\" = " + QString::number(current_client_id) + ");";
    qDebug() << query;
    return query;

}

void ClientEditForm::on_delete_button_clicked()
{
    QString query_line = this->generate_query_delete();
    QSqlQuery query(config::db);
    if(!query.exec(query_line))
    {
        qDebug() << query.lastError().text();
    }
    close();

}
