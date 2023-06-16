#ifndef PERSONEL_H
#define PERSONEL_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>

namespace Ui {
class personel;
}

class personel : public QDialog
{
    Q_OBJECT

public:
    explicit personel(QSqlDatabase veritabani, QWidget *parent = nullptr);
    ~personel();

    void listele();

private slots:
    void on_pushButton_kaydet_clicked();

    void on_pushButton_degistir_clicked();

    void on_pushButton_sil_clicked();

    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::personel *ui;

    QSqlQuery *sorgu;

    QSqlQueryModel *model;
};

#endif // PERSONEL_H
