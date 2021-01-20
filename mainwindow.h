#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <iostream>
#include <QSqlRecord>
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQueryModel>


#include "customform.h"
#include "insertclient.h"
#include "clienteditform.h"
#include "adddoctorform.h"
#include "doctoreditform.h"
#include "addsalonform.h"
#include "saloneditform.h"
#include "addappoinmentinfoform.h"
#include "addappform.h"


//#include <libpq>
//#include <QtCore/QtPlugin>
//Q_IMPORT_PLUGIN(qsqlpsql)

#include <QDate>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_sb_page_number_textChanged(const QString &arg1);

    void on_sb_page_size_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_addclientbutton_clicked();

    void on_submit_button_clicked();

    void on_table_doubleClicked(const QModelIndex &index);

    void on_page_size_textChanged(const QString &arg1);

    void on_page_number_textChanged(const QString &arg1);

    void on_doctor_filter_button_clicked();

    void on_edit_doctor_button_clicked();

    void on_add_new_doctor_button_clicked();

    void on_doctors_table_doubleClicked(const QModelIndex &index);

    void on_salon_page_size_textChanged(const QString &arg1);

    void on_salon_page_number_textChanged(const QString &arg1);

    void on_activate_salon_filter_button_clicked();

    void on_insert_salon_button_clicked();

    void on_salon_table_doubleClicked(const QModelIndex &index);

    void on_edit_salon_button_clicked();

    void on_app_page_number_textChanged(const QString &arg1);

    void on_app_page_size_textChanged(const QString &arg1);

    void on_app_filter_button_clicked();

    void on_app_info_button_clicked();

    void on_app_table_doubleClicked(const QModelIndex &index);

    void on_app_add_button_clicked();

private:

    Ui::MainWindow *ui;
    //QSqlDatabase db;
    customForm nextform;
    QSqlTableModel * client_table_model;
    void fill_client_table();
    QString filter_string();
    InsertClient form_insert;
    ClientEditForm *client_edit_form;


    //doctors
    void fill_doctor_table();
    QSqlTableModel * doctor_table_model;
    QString generate_doctor_filter();
    AddDoctorForm * doctor_form_insert;
    DoctorEditForm * doctor_edit_form;

    //salons
    void fill_salon_table();
    QSqlTableModel* salon_table_model;
    QString generate_salon_filter();
    AddSalonForm* salon_form_insert;
    SalonEditForm* salon_edit_form;

    //appoints
    void fill_app_table();
    QSqlTableModel* app_table_model;
    QString generate_app_filter();
    AddAppoinmentInfoForm* info_form;
    AddAppForm* add_app_form;

};
#endif // MAINWINDOW_H
