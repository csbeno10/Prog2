#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "std_lib_facilities.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected slots:

    void ResizeBig();

    void ResizeSmall();

    QLabel* Keres(string def);

    void BankJon();

    void Eredmeny();


private slots:


    void on_kerek_clicked();


    void on_szamolas_clicked();

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
