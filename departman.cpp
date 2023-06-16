#include "departman.h"
#include "ui_departman.h"

departman::departman(QSqlDatabase veritabani, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::departman)
{
    ui->setupUi(this);
    sorgu = new QSqlQuery(veritabani);

    listele();
}

departman::~departman()
{
    delete ui;
}

void departman::listele()
{
    sorgu->prepare("select * from departman_tablosu");
    if(!sorgu->exec()){
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Ok");
        return;
    }

    model = new QSqlQueryModel();
    model->setQuery(*sorgu);
    ui->tableView->setModel(model);
}

void departman::on_tableView_clicked(const QModelIndex &index)
{
    ui->lineEdit_departman_id->setText(model->index(index.row(),0).data().toString());
    ui->lineEdit_departman_ad->setText(model->index(index.row(),1).data().toString());
}


void departman::on_pushButton_kaydet_clicked()
{
    sorgu->prepare("insert into departman_tablosu(departman_ad) values(?)");
    sorgu->addBindValue(ui->lineEdit_departman_ad->text());

    if(!sorgu->exec()){
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
    }

    listele();
}


void departman::on_pushButton_guncelle_clicked()
{
    sorgu->prepare("update departman_tablosu set departman_ad=? where departman_no=?");
    sorgu->addBindValue(ui->lineEdit_departman_ad->text());
    sorgu->addBindValue(ui->lineEdit_departman_id->text().toInt());

    if(!sorgu->exec()){
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
    }

    listele();
}


void departman::on_pushButton_sil_clicked()
{
    sorgu->prepare("select * from personel_tablosu where departman_no=?");
    sorgu->addBindValue(ui->lineEdit_departman_id->text().toInt());

    if(!sorgu->exec()){
        QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
    }

    int sayac=0;
    while(sorgu->next()){
        sayac++;
    }
    if(sayac>0){
        QMessageBox::critical(this,"Hata","Departman silinemez, kayitli insan var.","Okay");
        return;
    }
    else{
        sorgu->prepare("delete from departman_tablosu where departman_no=?");
        sorgu->addBindValue(ui->lineEdit_departman_id->text().toInt());
        if(!sorgu->exec()){
            QMessageBox::critical(this,"Hata",sorgu->lastError().text(),"Okay");
        }
    }

    listele();
}

