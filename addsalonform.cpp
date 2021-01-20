#include "addsalonform.h"
#include "ui_addsalonform.h"

AddSalonForm::AddSalonForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddSalonForm)
{
    ui->setupUi(this);
}

AddSalonForm::~AddSalonForm()
{
    delete ui;
}

void AddSalonForm::clear_all_fields()
{
    ui->salon_city_edit->setText("");
    ui->salon_country_edit->setText("");
    ui->salon_apart_edit->setText("");
    ui->salon_street_edit->setText("");
    ui->salon_name_edir->setText("");
    ui->salon_house_edit->setText("");

}

void AddSalonForm::on_salon_cancel_button_clicked()
{
    close();
}

void AddSalonForm::on_salon_add_buton_clicked()
{
    QString salon_name = ui->salon_name_edir->text();
    QString salon_country  =ui->salon_country_edit->text();
    QString salon_city = ui->salon_city_edit->text();
    QString salon_street = ui->salon_street_edit->text();
    QString number_str = ui->salon_house_edit->text();
    QString apart_str = ui->salon_apart_edit->text();
    bool int_check_flag;
    number_str.toInt(&int_check_flag);
    apart_str.toInt(&int_check_flag);
    if(!int_check_flag)
    {
        QMessageBox::warning(this, "Attention", "Incorrect integer values");
    }
    else
    {
        if(salon_name != "" && salon_country != "" && salon_city != "" and salon_street != "" and number_str != "")
        {
            QSqlQuery query(config::db);
            QString query_line = "select \"OpenNewSalon\"(";
            query_line += "'" + salon_name + "', ";
            query_line += "'" + salon_country + "', ";
            query_line += "'" + salon_city + "', ";
            query_line += "'" + salon_street + "', ";
            query_line += number_str;
            if(apart_str != "")
            {
                query_line += ", " + apart_str;
            }
            query_line += ");";
            if(!query.exec(query_line))
            {
                QMessageBox::warning(this, "Attention", query.lastError().text());
            }
            this->hide();
        }
        else
        {
            QMessageBox::warning(this, "Attention", "Incorrect values");
        }
    }

}
