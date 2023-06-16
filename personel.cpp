#include "personel.h"
#include "ui_personel.h"

personel::personel(QSqlDatabase veritabani, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::personel)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(veritabani);
    listele();
}

personel::~personel()
{
    delete ui;
}

void personel::listele()
{
    sorgu->prepare("SELECT * FROM personel_tablosu");
    if(!sorgu->exec()){
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Ok");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView->setModel(model);
}

void personel::on_pushButton_kaydet_clicked()
{
    sorgu->prepare("insert into personel_tablosu(personel_ad, personel_soyad, departman_no) values(?,?,?)");
    sorgu->addBindValue(ui->lineEdit_personel_ad->text());
    sorgu->addBindValue(ui->lineEdit_personel_soyad->text());
    sorgu->addBindValue(ui->lineEdit_departman_no->text().toInt());

    if(!sorgu->exec()){
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
    }

    listele();
}


void personel::on_pushButton_degistir_clicked()
{
    sorgu->prepare("update personel_tablosu set personel_ad=?,personel_soyad=?,departman_no=? where personel_no=?");
    sorgu->addBindValue(ui->lineEdit_personel_ad->text());
    sorgu->addBindValue(ui->lineEdit_personel_soyad->text());
    sorgu->addBindValue(ui->lineEdit_departman_no->text().toInt());
    sorgu->addBindValue(ui->lineEdit_personel_no->text().toInt());

    if(!sorgu->exec()){
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
    }

    listele();
}


void personel::on_pushButton_sil_clicked()
{
    sorgu->prepare("delete from personel_tablosu where personel_no=?");
    sorgu->addBindValue(ui->lineEdit_personel_no->text().toInt());

    if(!sorgu->exec()){
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
    }

    listele();
}


void personel::on_tableView_clicked(const QModelIndex &index)
{
    ui->lineEdit_personel_no->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_personel_ad->setText(model->index(index.row(),1).data().toString());
    ui->lineEdit_personel_soyad->setText(model->index(index.row(),2).data().toString());
    ui->lineEdit_departman_no->setText(model->index(index.row(),3).data().toString());
}
