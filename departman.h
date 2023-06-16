#ifndef DEPARTMAN_H
#define DEPARTMAN_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QSqlError>

namespace Ui {
class departman;
}

class departman : public QDialog
{
    Q_OBJECT

public:
    explicit departman(QSqlDatabase veritabani, QWidget *parent = nullptr);
    ~departman();

    void listele();

private slots:
    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_kaydet_clicked();

    void on_pushButton_guncelle_clicked();

    void on_pushButton_sil_clicked();

private:
    Ui::departman *ui;

    QSqlQuery *sorgu;

    QSqlQueryModel *model;
};

#endif // DEPARTMAN_H
