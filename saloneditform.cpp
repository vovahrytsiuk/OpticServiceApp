#include "saloneditform.h"
#include "ui_saloneditform.h"

SalonEditForm::SalonEditForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SalonEditForm)
{
    ui->setupUi(this);
    this->mapper  =new QDataWidgetMapper();
}

SalonEditForm::~SalonEditForm()
{
    delete ui;
}

void SalonEditForm::setModel(QAbstractItemModel *mod)
{

    this->mapper->setModel(mod);

    this->mapper->addMapping(ui->salon_id_data, 0);

    this->mapper->addMapping(ui->salon_new_name_edit, 1);

    this->mapper->addMapping(ui->salon_new_country_edit, 2);

    this->mapper->addMapping(ui->salon_new_city_edit, 3);

    this->mapper->addMapping(ui->salon_new_street_edit, 4);

    this->mapper->addMapping(ui->salon_new_house_edit, 5);

    this->mapper->addMapping(ui->salon_new_apart_edit, 6);

}

QString SalonEditForm::generate_update_query()
{
    int current_salon_id = this->read_salon_id();
    QString query = "select \"UpdateSalon\"(";
    QString new_salon_name = ui->salon_new_name_edit->text();
    QString new_salon_country = ui->salon_new_country_edit->text();
    QString new_salon_city = ui->salon_new_city_edit->text();
    QString new_salon_street = ui->salon_new_street_edit->text();
    QString new_salon_house = ui->salon_new_house_edit->text();
    QString new_salon_apart = ui->salon_new_apart_edit->text();
    bool int_check_flag;
    new_salon_house.toInt(&int_check_flag);
    new_salon_apart.toInt(&int_check_flag);
    if(!int_check_flag)
    {
        //QMessageBox::warning(this, "Attention", "Incorrect integer values");
        query = "";
    }
    else
    {
        if(new_salon_name != "" && new_salon_country != "" && new_salon_city != "" && new_salon_street != "" && new_salon_house != "")
        {
            query += QString::number(current_salon_id) + ", ";
            query += "'" + new_salon_name + "', ";
            query += "'" + new_salon_country + "', ";
            query += "'" + new_salon_city + "', ";
            query += "'" + new_salon_street + "', ";
            query += "" + new_salon_house + "";
            if(new_salon_apart != "")
            {
                query += ", " + new_salon_apart + "";
            }
            query += ");";
            qDebug() << query;

        }
        else
        {
            //QMessageBox::warning(this, "Attention", "Invalid paramentrs");
            query = "";
        }

    }
    return query;

}

QString SalonEditForm::generate_delete_query()
{

    int current_salon_id = this->read_salon_id();
    QString query = "delete from \"Salons\" where \"SalonID\" = " + QString::number(current_salon_id);
    return query;

}

int SalonEditForm::read_salon_id()
{
    return ui->salon_id_data->text().toInt();
}

void SalonEditForm::on_salon_update_button_clicked()
{
    QSqlQuery query(config::db);
    QString query_line = this->generate_update_query();
    if (query_line == "")
    {
        QMessageBox::warning(this, "Attention", "InvalidParamentrs");
        return;
    }
    if(!query.exec(query_line))
    {
        qDebug() << query.lastError().text();
    }
    close();
}






void SalonEditForm::on_salon_cancel_button_clicked()
{
    close();
}

void SalonEditForm::on_salon_delete_button_clicked()
{
    QSqlQuery query (config::db);
    if (!query.exec(this->generate_delete_query()))
    {
        qDebug() << query.lastError().text();
    }
    close();
}
