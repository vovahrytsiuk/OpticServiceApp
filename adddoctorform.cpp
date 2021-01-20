#include "adddoctorform.h"
#include "ui_adddoctorform.h"

AddDoctorForm::AddDoctorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDoctorForm)
{
    ui->setupUi(this);
}

AddDoctorForm::~AddDoctorForm()
{
    delete ui;
}

void AddDoctorForm::clear_all_fields()
{
    ui->le_doctor_firstname->setText("");
    ui->le_doctor_lastname->setText("");
    ui->le_doctor_specialisation->setText("");
}



void AddDoctorForm::on_add_doctor_button_clicked()
{
    QString firstName = ui->le_doctor_firstname->text();
    QString lastName =  ui->le_doctor_lastname->text();
    QString sex = ui->cb_doctor_sex->currentText();
    QDate birth = ui->de_doctor_birthdate->date();
    QString spec = ui->le_doctor_specialisation->text();
    QString birthDate = date_to_postgre(birth);
    QSqlQuery* query = new QSqlQuery(config::db);
    if(firstName != "" && lastName != "" && spec != "")
    {
    QString query_string = "select \"AddNewDoctor\"('";
    query_string += firstName + "','";
    query_string += lastName + "',";
    query_string += birthDate + ",'";
    query_string += sex + "','";
    query_string += spec + "')";
    query->exec(query_string);
    qDebug() << query_string;
    qDebug() << query->lastError().text();
    this->hide();
    }
    else
    {
        QMessageBox::warning(this, "Attention", "Invalid paramentrs");
    }
    this->clear_all_fields();



}

void AddDoctorForm::on_doctor_cancel_clicked()
{
    this->clear_all_fields();
    close();
}
