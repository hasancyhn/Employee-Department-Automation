#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "personel.h"
#include "departman.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    veritabani.setDatabaseName("C:/Users/HASAN/Documents/Bahar23GP_Lab12_VeriTabaniIslemleri/personel.db");
    if(!veritabani.open()){
        ui->statusbar->showMessage("Veri tabanına bağlanamadı.");
    }
    else{
         ui->statusbar->showMessage("Veri tabanına bağlandı");
    }

    model_1 = new QSqlTableModel();
    model_1->setTable("departman_tablosu");
    model_1->select();
    ui->tableView_department->setModel(model_1);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_tableView_department_clicked(const QModelIndex &index)
{
    // Tiklanan satirdaki veri alinir.
    QString departman = model_1->index(index.row(), 0).data().toString();
    int departmanNumarasi = departman.toInt();
    QSqlQuery sorgu;
    sorgu.prepare("SELECT * FROM personel_tablosu WHERE departman_no=?");
    sorgu.addBindValue(departmanNumarasi);
    sorgu.exec();

    model_2 = new QSqlQueryModel();
    model_2->setQuery(sorgu);
    ui->tableView_personal->setModel(model_2);
}


void MainWindow::on_pushButton_department_ekrani_clicked()
{
    departman *dep = new departman(veritabani);
    dep->show();
}


void MainWindow::on_pushButton_personel_ekrani_clicked()
{
    personel *per = new personel(veritabani);
    per->show();
}




