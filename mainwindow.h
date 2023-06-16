#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSql>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

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
    void on_pushButton_department_ekrani_clicked();

    void on_pushButton_personel_ekrani_clicked();

    void on_tableView_department_clicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;

    QSqlDatabase veritabani = QSqlDatabase::addDatabase("QSQLITE");

    QSqlTableModel *model_1;

    QSqlQueryModel *model_2;
};
#endif // MAINWINDOW_H
