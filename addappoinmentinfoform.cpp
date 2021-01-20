#include "addappoinmentinfoform.h"
#include "ui_addappoinmentinfoform.h"

AddAppoinmentInfoForm::AddAppoinmentInfoForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddAppoinmentInfoForm)
{
    ui->setupUi(this);
    this->mapper = new QDataWidgetMapper(this);
}

AddAppoinmentInfoForm::~AddAppoinmentInfoForm()
{
    delete ui;
}

void AddAppoinmentInfoForm::setModel(QAbstractItemModel* mod)
{


    this->mapper->setModel(mod);

    this->mapper->addMapping(ui->app_id_edit, 0);





}

void AddAppoinmentInfoForm::fill_table()
{
    model = new QSqlTableModel(this, config::db);
    model->setTable("\"AppointmentPersons\"");
    QString id = ui->app_id_edit->text();
    QString line = "\"AppointmentID\" = " + id;
    model->setFilter(line);
    qDebug() << line;
    model->select();
    ui->add_info_table->setModel(model);
}

void AddAppoinmentInfoForm::on_close_button_clicked()
{
    close();
}
