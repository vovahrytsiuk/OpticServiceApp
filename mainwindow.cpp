#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->db = QSqlDatabase::addDatabase("QPSQL");
//    this->db.setHostName("127.0.0.1");
//    this->db.setDatabaseName("Optic");
//    this->db.setUserName("receptionist");
//    this->db.setPassword("jw8s0f4");
//    if (!this->db.open())
//    {
//        std::cout <<"no connection"  << std::endl;

//    }
//    else
//    {
//        std::cout << "Connection sucsessfully" << std::endl;
//    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    config::user_name = ui->edit_login->text();
    config::user_password = ui->edit_password->text();

    config::db = QSqlDatabase::addDatabase("QPSQL");
    config::db.setHostName("127.0.0.1");
    config::db.setDatabaseName("Optic");
    config::db.setUserName(config::user_name);
    config::db.setPassword(config::user_password);
    if (!config::db.open())
    {
        QMessageBox::warning(this, "Attention", config::db.lastError().text());
    }
    else
    {
        ui->tabWidget->widget(0)->deleteLater();
        this->fill_client_table();


        this->client_edit_form = new ClientEditForm();
        this->client_edit_form->setParent(this, Qt::Window);
        this->client_edit_form->setModel(this->client_table_model);







        this->fill_doctor_table();
        this->doctor_form_insert = new AddDoctorForm();
        this->doctor_form_insert->setParent(this, Qt::Window);
        this->doctor_edit_form = new DoctorEditForm();
        this->doctor_edit_form->setParent(this, Qt::Window);
        this->doctor_edit_form->setModel(this->doctor_table_model);



        this->fill_salon_table();
        this->salon_form_insert = new AddSalonForm();
        this->salon_form_insert->setParent(this, Qt::Window);

        this->salon_edit_form = new SalonEditForm();
        this->salon_edit_form->setParent(this, Qt::Window);
        this->salon_edit_form->setModel(this->salon_table_model);



        this->fill_app_table();
        this->info_form = new AddAppoinmentInfoForm();
        this->info_form->setParent(this, Qt::Window);
        this->info_form->setModel(this->doctor_table_model);
        this->add_app_form = new AddAppForm();
        this->add_app_form->setParent(this, Qt::Window);
        this->add_app_form->setClientModel(this->client_table_model);
        this->add_app_form->setDoctorModel(this->doctor_table_model);
        this->add_app_form->setSalonModel(this->salon_table_model);

    }

}



void MainWindow::fill_client_table()
{
    ui->table->hide();
    //std::cout << "start" << std::endl;
    int page_number = ui->sb_page_number->text().toInt();
    int page_size = ui->sb_page_size->text().toInt();
    QSqlQuery *query = new QSqlQuery( config::db);

    if (!query->exec("select * from \"ClientsView\""))
    {
        //std::cout << "bad";
        QMessageBox::warning(this, "Attention", query->lastError().text());
    }

    this->client_table_model = new QSqlTableModel(this);
    this->client_table_model->setTable("\"ClientsView\"");
    this->client_table_model->setFilter(this->filter_string());



    this->client_table_model->select();

    int low_index = (page_number - 1) * page_size;
    int high_index = page_number * page_size;

    //std::cout << low_index << " " << high_index << std::endl;

    int i = 0;
    //std::cout << "ready for cycle" << std::endl;
    int number_records  = query->size();





    //std::cout << "set model" << std::endl;
    ui->table->setModel(this->client_table_model);
    for(; i < number_records; i++){
        if(i >= low_index && i < high_index){
            ui->table->showRow(i);
        }
        else{
            ui->table->hideRow(i);
        }
    }
    ui->table->show();
}

void MainWindow::on_sb_page_number_textChanged(const QString &arg1 )
{
    delete this->client_table_model;
    this->fill_client_table();
}

void MainWindow::on_sb_page_size_textChanged(const QString &arg1)
{
    delete this->client_table_model;
    this->fill_client_table();

}


QString MainWindow::filter_string()
{
    QString filter = "";
    QString sex_filter = ui->sex_filter->currentText();
    if (sex_filter != "")
    {
        filter += "\"Sex\" like '%" + sex_filter + "%'";
    }
    //add first name filtration
    QString first_name_filter = ui->firstName_filter->text();
    if(first_name_filter != "")
    {
        if(filter != "")
        {
            filter += " and ";
        }
        filter += "\"FirstName\" like '%" + first_name_filter + "%'";

    }
    //add last name filtration
    QString last_name_filter = ui->lastName_filter->text();
    if(last_name_filter != "")
    {
        if(filter != "")
        {
            filter += " and ";
        }
        filter += "\"LastName\" like '%" + last_name_filter + "%'";
    }
    //add date filter
    QDate start = ui->dateEdit_start->date();
    QDate finish = ui->dateEdit_finish->date();
    if (start > finish){
        QMessageBox::warning(this, "Attention", "Start date is more than finish date");
        return filter;
    }
    else{
        if (filter != "")
        {
            filter += " and ";
        }
        //'pppp-mm-dd'
        filter += "(\"BirthDate\" between ";
        int start_year = start.year();
        int start_month = start.month();
        int start_day = start.day();
        filter += "'" + QString::number(start_year) + "-" + QString::number(start_month) + "-" + QString::number(start_day) + "'";
        filter += " and ";
        int finish_year = finish.year();
        int finish_month = finish.month();
        int finish_day = finish.day();
        filter += "'" + QString::number(finish_year) + "-" + QString::number(finish_month) + "-" + QString::number(finish_day) + "')";
    }
    qDebug() << filter;
    return filter;
}

void MainWindow::fill_doctor_table()
{
    ui->doctors_table->hide();
    int page_number = ui->page_number->text().toInt();
    int page_size = ui->page_size->text().toInt();

    QSqlQuery query(config::db);
    if(!query.exec("select * from \"DoctorsView\""))
    {
        QMessageBox::warning(this, "Attention", query.lastError().text());
    }

    this->doctor_table_model = new QSqlTableModel(this, config::db);
    this->doctor_table_model->setTable("\"DoctorsView\"");
    this->doctor_table_model->select();
    this->doctor_table_model->setFilter(this->generate_doctor_filter());


    int low_index = (page_number - 1) * page_size;
    int high_index = page_number * page_size;

    std::cout << low_index << " " << high_index << std::endl;

    int number_records = query.size();
    ui->doctors_table->setModel(this->doctor_table_model);
    for(int i = 0; i < number_records; i++)
    {
        if(i >= low_index && i < high_index)
        {
            ui->doctors_table->showRow(i);
        }
        else
        {
            ui->doctors_table->hideRow(i);
        }
    }
    ui->doctors_table->show();

}

QString MainWindow::generate_doctor_filter()
{
    QString filter = "";
    QString sex_filter = ui->doctor_sex_edit->currentText();
    if (sex_filter != "")
    {
        filter += "\"Sex\" like '%" + sex_filter + "%'";
    }

    //add first name filtration
    QString first_name_filter = ui->doctor_firstname_edit->text();
    if(first_name_filter != "")
    {
        if(filter != "")
        {
            filter += " and ";
        }
        filter += "\"FirstName\" like '%" + first_name_filter + "%'";

    }

    //add last name filtration
    QString last_name_filter = ui->doctor_last_name_edit->text();
    if(last_name_filter != "")
    {
        if(filter != "")
        {
            filter += " and ";
        }
        filter += "\"LastName\" like '%" + last_name_filter + "%'";
    }
    //add specialisation filter
    QString spec_filter = ui->spec_filter->text();
    if(spec_filter != "")
    {
        if(filter != "")
        {
            filter += " and ";
        }
        filter += "\"Specialisation\" like '%" + spec_filter + "%'";
    }

    //add date filter
    QDate start = ui->doctor_date_start_edit->date();
    QDate finish = ui->doctor_finish_date_edit->date();
    if (start > finish){
        QMessageBox::warning(this, "Attention", "Start date is more than finish date");
        return filter;
    }
    else{
        if (filter != "")
        {
            filter += " and ";
        }
        //'pppp-mm-dd'
        filter += "(\"BirthDate\" between ";
        int start_year = start.year();
        int start_month = start.month();
        int start_day = start.day();
        filter += "'" + QString::number(start_year) + "-" + QString::number(start_month) + "-" + QString::number(start_day) + "'";
        filter += " and ";
        int finish_year = finish.year();
        int finish_month = finish.month();
        int finish_day = finish.day();
        filter += "'" + QString::number(finish_year) + "-" + QString::number(finish_month) + "-" + QString::number(finish_day) + "')";
    }
    qDebug() << filter;
    return filter;

}

void MainWindow::fill_salon_table()
{
    ui->salon_table->hide();
    //std::cout << "start" << std::endl;
    int page_number = ui->salon_page_number->text().toInt();
    int page_size = ui->salon_page_size->text().toInt();
    QSqlQuery *query = new QSqlQuery( config::db);

    if (!query->exec("select * from \"SalonView\""))
    {
        //std::cout << "bad";
        QMessageBox::warning(this, "Attention", query->lastError().text());
    }

    this->salon_table_model = new QSqlTableModel(this);
    this->salon_table_model->setTable("\"SalonView\"");
    this->salon_table_model->setFilter(this->generate_salon_filter());



    this->salon_table_model->select();

    int low_index = (page_number - 1) * page_size;
    int high_index = page_number * page_size;

    //std::cout << low_index << " " << high_index << std::endl;

    int i = 0;
    //std::cout << "ready for cycle" << std::endl;
    int number_records  = query->size();





    //std::cout << "set model" << std::endl;
    ui->salon_table->setModel(this->salon_table_model);
    for(; i < number_records; i++){
        if(i >= low_index && i < high_index){
            ui->salon_table->showRow(i);
        }
        else{
            ui->salon_table->hideRow(i);
        }
    }
    ui->salon_table->show();
}

QString MainWindow::generate_salon_filter()
{
    QString filter = "";
    QString name_filter = ui->salon_name_edit->text();
    if(name_filter != "")
    {
        filter += "\"SalonName\" like '%" + name_filter + "%' ";
    }
    QString country_filter = ui->country_edit->text();
    if(country_filter != "")
    {
        if(filter != "")
        {
            filter += " and ";
        }
        filter += "\"CountryName\" = '" + country_filter + "'";
    }
    QString city_filter = ui->city_edit->text();
    if(city_filter != "")
    {
        if(filter != "")
        {
            filter += " and ";
        }
        filter += "\"CityName\" = '" + city_filter + "'";
    }
    QString street_filter = ui->street_edit->text();
    if(street_filter != "")
    {
        if(filter != "")
        {
            filter += " and ";
        }
        filter += "\"StreetName\" = '" + street_filter + "'";
    }
    qDebug() << filter;
    return filter;
}

void MainWindow::fill_app_table()
{
    int page_number = ui->app_page_number->text().toInt();
    int page_size = ui->app_page_size->text().toInt();
    int low_index = (page_number - 1) * page_size;
    int high_index = page_number * page_size;
    QSqlQuery query(config::db);
    if(!query.exec("select * from \"AppointmentsView\""))
    {
        QMessageBox::warning(this, "Attention", query.lastError().text());
    }
    int records_count = query.size();


    this->app_table_model = new QSqlTableModel(this, config::db);
    this->app_table_model->setTable("\"AppointmentsView\"");
    this->app_table_model->setFilter(this->generate_app_filter());
    this->app_table_model->select();


    ui->app_table->setModel(this->app_table_model);
    for(int i = 0; i < records_count; i++){
        if(i >= low_index && i < high_index){
            ui->app_table->showRow(i);
        }
        else{
            ui->app_table->hideRow(i);
        }
    }


}

QString MainWindow::generate_app_filter()
{
    QString filter = "";
    QString clientid = ui->app_client_id_edit->text();
    if(clientid != "")
    {
        bool check;
        clientid.toInt(&check);
        if(!check)
        {
            QMessageBox::warning(this, "Attention", "Invalid integer parametr");
            return "";
        }
        filter += "\"ClientID\" = " + clientid;
    }
    QString doctorid = ui->app_doctor_id_edit->text();
    if(doctorid != "")
    {
        bool check;
        doctorid.toInt(&check);
        if(!check)
        {
            QMessageBox::warning(this, "Attention", "Invalid integer parametr");
            return "";
        }
        if (filter != "")
        {
            filter += " and ";
        }
        filter += "\"DoctorID\" = " + doctorid;
    }
    QString name = ui->app_salon_name_edit->text();
    if(name != "")
    {
        if(filter != "")
        {
            filter += " and ";
        }
        filter += "\"SalonName\" like '%" + name + "%'";
    }



    //add date filter
    QDate start = ui->app_first_date_edit->date();
    QDate finish = ui->app_lat_date_edit->date();
    if (start > finish){
        QMessageBox::warning(this, "Attention", "Start date is more than finish date");
        return "";
    }
    else{
        if (filter != "")
        {
            filter += " and ";
        }
        //'pppp-mm-dd'
        filter += "(\"Date\" between ";
        int start_year = start.year();
        int start_month = start.month();
        int start_day = start.day();
        filter += "'" + QString::number(start_year) + "-" + QString::number(start_month) + "-" + QString::number(start_day) + "'";
        filter += " and ";
        int finish_year = finish.year();
        int finish_month = finish.month();
        int finish_day = finish.day();
        filter += "'" + QString::number(finish_year) + "-" + QString::number(finish_month) + "-" + QString::number(finish_day) + "')";
    }
    QString status = ui->app_status_edit->text();
    if(status != ""){
        if(filter != "")
        {
            filter += " and ";
        }
        filter += "\"StatusValue\" like '%" + status + "%'";
    }
    qDebug() << filter;
    return filter;

}

void MainWindow::on_pushButton_2_clicked()
{
    delete this->client_table_model;
    this->fill_client_table();
}

void MainWindow::on_addclientbutton_clicked()
{
    this->form_insert.clear_all_fields();
    this->form_insert.show();
    delete this->client_table_model;
    this->fill_client_table();
}

void MainWindow::on_submit_button_clicked()
{
    this->client_edit_form->setModel(this->client_table_model);
    this->client_edit_form->show();

}

void MainWindow::on_table_doubleClicked(const QModelIndex &index)
{
    this->client_edit_form->setModel(this->client_table_model);
    this->client_edit_form->mapper->setCurrentModelIndex(index);
    this->add_app_form->setClientModel(this->client_table_model);
    this->add_app_form->mapper_client->setCurrentModelIndex(index);
}

void MainWindow::on_page_size_textChanged(const QString &arg1)
{
    delete this->doctor_table_model;
    this->fill_doctor_table();
}

void MainWindow::on_page_number_textChanged(const QString &arg1)
{
    delete this->doctor_table_model;
    this->fill_doctor_table();
}

void MainWindow::on_doctor_filter_button_clicked()
{
    delete this->doctor_table_model;
    this->fill_doctor_table();
}

void MainWindow::on_edit_doctor_button_clicked()
{
    this->doctor_edit_form->setModel(this->doctor_table_model);
    this->doctor_edit_form->show();
}

void MainWindow::on_add_new_doctor_button_clicked()
{
    this->doctor_form_insert->clear_all_fields();
    this->doctor_form_insert->show();
    delete this->doctor_table_model;
    this->fill_doctor_table();
}

void MainWindow::on_doctors_table_doubleClicked(const QModelIndex &index)
{
    this->doctor_edit_form->setModel(this->doctor_table_model);
    this->doctor_edit_form->mapper->setCurrentModelIndex(index);
    this->add_app_form->setDoctorModel(this->doctor_table_model);
    this->add_app_form->mapper_doctor->setCurrentModelIndex(index);

}

void MainWindow::on_salon_page_size_textChanged(const QString &arg1)
{
    delete this->salon_table_model;
    this->fill_salon_table();
}

void MainWindow::on_salon_page_number_textChanged(const QString &arg1)
{
    delete this->salon_table_model;
    this->fill_salon_table();
}

void MainWindow::on_activate_salon_filter_button_clicked()
{
    delete this->salon_table_model;
    this->fill_salon_table();
}

void MainWindow::on_insert_salon_button_clicked()
{
    this->salon_form_insert->clear_all_fields();
    this->salon_form_insert->show();
}

void MainWindow::on_salon_table_doubleClicked(const QModelIndex &index)
{
    this->salon_edit_form->setModel(this->salon_table_model);
    this->salon_edit_form->mapper->setCurrentModelIndex(index);
    this->add_app_form->setSalonModel(this->salon_table_model);
    this->add_app_form->mapper_salon->setCurrentModelIndex(index);
}

void MainWindow::on_edit_salon_button_clicked()
{
    this->salon_edit_form->setModel(this->salon_table_model);
    this->salon_edit_form->show();
}

void MainWindow::on_app_page_number_textChanged(const QString &arg1)
{
    delete this->app_table_model;
    this->fill_app_table();
}

void MainWindow::on_app_page_size_textChanged(const QString &arg1)
{
    delete this->app_table_model;
    this->fill_app_table();
}

void MainWindow::on_app_filter_button_clicked()
{
    delete this->app_table_model;
    this->fill_app_table();
}

void MainWindow::on_app_info_button_clicked()
{
    this->info_form->setModel(this->app_table_model);
    this->info_form->show();
    this->info_form->fill_table();
}

void MainWindow::on_app_table_doubleClicked(const QModelIndex &index)
{
    this->info_form->setModel(this->app_table_model);
    this->info_form->mapper->setCurrentModelIndex(index);

}

void MainWindow::on_app_add_button_clicked()
{
    this->add_app_form->show();
}
