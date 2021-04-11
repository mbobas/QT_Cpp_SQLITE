#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //oddajemy baze o danym typie
    // dla bazy posgres wiecej zmiennym, http, login, pass
    QSqlDatabase baza = QSqlDatabase::addDatabase("QSQLITE");

    //jesli plik nie zostanie odnaleziony to QT tworzy nowa baze
    //baza danych musi byc w katalogu build lub pelna sciezka
    //\QT\build-nienazwany-Desktop_Qt_5_15_1_MinGW_64_bit-Debug

    baza.setDatabaseName("plan_nsi.db");
    if(!baza.open()) {
        qDebug()<<"Blad polaczenia";
    }else {
        qDebug()<<"Polaczono";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->textEdit->clear();
    //zapytanie zwraca boola
    QSqlQuery zapytanie;

    //query z pola tekstowego
    QString tekst;
    tekst = ui->lineEdit->text();

    bool sukces = zapytanie.exec(tekst);
    qDebug() << sukces;
    //pobieramy ilosc pol
    int ile_pol = zapytanie.record().count();
    //iterujemy po wszytkich rekordach zwroconych przez zpaytanie
    while(zapytanie.next())
    {
        //consola
        //qDebug()<<zapytanie.value(0).toString()<<""<<zapytanie.value(1).toString();
        QString t = "";
        for (int i=0; i<ile_pol; i++){
            t +=zapytanie.value(i).toString()+" ";
        }

        ui->textEdit->append(t);

    }
}

void MainWindow::on_pushButton_2_clicked()
{
    QString nazwa, pojemnosc;
    nazwa = ui->lineEdit_2->text();
    pojemnosc = ui->lineEdit_3->text();

    QSqlQuery zapytanie;
    zapytanie.prepare("INSERT INTO sale(nazwa_sali, pojemnosc) VALUES (:nazwa, :pojemnosc);");
    zapytanie.bindValue(":nazwa", nazwa);
    zapytanie.bindValue("pojemnosc", pojemnosc);
    bool sukces = zapytanie.exec();
    qDebug() << sukces;
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->tableWidget->clear();
    //zapytanie zwraca boola
    QSqlQuery zapytanie;

    //query z pola tekstowego
    QString tekst;
    tekst = ui->lineEdit->text();

    bool sukces = zapytanie.exec(tekst);
    qDebug() << sukces;

    int ile_pol = zapytanie.record().count();
    ui->tableWidget->setColumnCount(ile_pol);
    ui->tableWidget->setRowCount(0);

    //pobieramy ilosc pol
    int wiersz =0;
    //iterujemy po wszytkich rekordach zwroconych przez zpaytanie
    while(zapytanie.next())
    {
        ui->tableWidget->insertRow(wiersz);
        for (int i=0; i<ile_pol; i++){
            ui->tableWidget->setItem(wiersz,i, new QTableWidgetItem(zapytanie.value(i).toString()+" "));
        }

    wiersz++;

    }

}

void MainWindow::on_pushButton_4_clicked()
{
    //query z pola tekstowego
    QString tekst;
    tekst = ui->lineEdit->text();
    QSqlQueryModel *zapytanie = new QSqlQueryModel;
    zapytanie->setQuery(tekst);
    ui->tableView->setModel(zapytanie);
    ui->tableView->show();


}
