#include "doctoreditform.h"
#include "ui_doctoreditform.h"

DoctorEditForm::DoctorEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DoctorEditForm)
{
    ui->setupUi(this);
    this->mapper = new QDataWidgetMapper(this);
}

DoctorEditForm::~DoctorEditForm()
{
    delete ui;
}

void DoctorEditForm::setModel(QAbstractItemModel *mod)
{
    this->mapper->setModel(mod);
    this->mapper->addMapping(ui->doctor_id_data, 0);
    this->mapper->addMapping(ui->doctor_first_name_edit, 1);
    this->mapper->addMapping(ui->doctor_last_name_edit, 2);
    this->mapper->addMapping(ui->doctor_dateEdit, 3);
    this->mapper->addMapping(ui->doctor_sex_edit, 4);
    this->mapper->addMapping(ui->spec_edit, 5);

}

QString DoctorEditForm::generate_update_query()
{
    int current_client_id = this->read_client_id();
    QString new_first_name = ui->doctor_first_name_edit->text();
    QString new_last_name = ui->doctor_last_name_edit->text();
    QString new_date = date_to_postgre(ui->doctor_dateEdit->date());
    QString new_sex = ui->doctor_sex_edit->currentText();
    QString new_spec = ui->spec_edit->toPlainText();
    qDebug() << new_spec;
    std::cout << "reary for creating query" << std::endl;
    if(new_first_name != "" && new_last_name != "" && new_spec != "")
    {
        QString query = "select \"UpdateDoctor\"(";
        query += QString::number(current_client_id) + ",";
        query += "'" + new_first_name + "'";
        query += " , ";
        query += "'" + new_last_name + "'";
        query += " , ";
        query += new_date;
        query += " , ";
        query += "'" + new_sex + "'";
        query += " , ";
        query += "'" + new_spec + "'";
        query +=")";
        qDebug() << query;
        return query;
    }
    return "";
}

QString DoctorEditForm::generate_delete_query()
{
    int current_client_id = this->read_client_id();
    QString query = " delete from \"Persons\" where \"PersonID\"  = (select \"PersonID\" from \"Doctors\" where \"DoctorID\" = " + QString::number(current_client_id) + ");";
    qDebug() << query;
    return query;
}

int DoctorEditForm::read_client_id()
{
    return ui->doctor_id_data->text().toInt();
}

void DoctorEditForm::on_update_button_clicked()
{
    QSqlQuery query(config::db);
    QString query_line = this->generate_update_query();
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

void DoctorEditForm::on_delete_button_clicked()
{
    QString query_line = this->generate_delete_query();
    QSqlQuery query(config::db);
    if(!query.exec(query_line))
    {
        qDebug() << query.lastError().text();
    }
    close();
}

void DoctorEditForm::on_cancell_button_clicked()
{
    close();
}
