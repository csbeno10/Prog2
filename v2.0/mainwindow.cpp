#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "std_lib_facilities.h"
#include <QString>
#include <QDesktopWidget>

struct Lap {
    string szim = "";
    int ertek = 0;
    bool volt = false;

    Lap() {};
    Lap(string sz, int ert) : szim{ sz }, ertek{ ert } {};

};

QString Huzas(vector<Lap>& pak, vector<Lap>& vec, int& szum)
{
    int hanyas;
    QString re;
    hanyas = rand() % pak.size();
    if (pak[hanyas].volt == true) re=Huzas(pak, vec, szum);
    else
    {
        Lap l = pak[hanyas];
        pak[hanyas].volt = true;
        vec.push_back(l);
        szum += l.ertek;
        re=QString::fromStdString(l.szim);
        return re;
    }
}

bool Aszkereso(vector<Lap>& vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i].szim == "A" && vec[i].ertek == 11)
        {
            vec[i].ertek = 1;
            return true;
        }
    }
    return false;
}


void Pakli(vector<Lap> lapok, vector<Lap>& pakli, int db)
{
    for (int i = 0; i < lapok.size(); i++)
    {
        for (int j = 0; j < db * 4; j++)
        {
            pakli.push_back(lapok[i]);
        }
    }
}

QString Valseg(vector<Lap> pak, vector<Lap> player, int sz, bool& ment)
{
    double jo = 0;
    for (int i = 0; i < pak.size(); i++)
    {
        if (pak[i].szim == "A") jo += 1;
        else if (sz + pak[i].ertek < 22) jo += 1;
    }
    for (int i = 0; i < player.size(); i++)
    {
        if (player[i].szim == "A" && player[i].ertek == 11) ment = true;
    }
    QString re=QString::fromStdString(to_string(jo / pak.size() * 100)+"%");
    return re;

}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->bank1->setVisible(false);
    ui->bank2->setVisible(false);
    ui->bank3->setVisible(false);
    ui->bank4->setVisible(false);
    ui->bank5->setVisible(false);
    ui->bank6->setVisible(false);
    ui->player1->setVisible(false);
    ui->player2->setVisible(false);
    ui->player3->setVisible(false);
    ui->player4->setVisible(false);
    ui->player5->setVisible(false);
    ui->player6->setVisible(false);
    ui->blap->setVisible(false);
    ui->mehet2->setVisible(false);
    connect(ui->mehet, SIGNAL(clicked()), this, SLOT(ResizeBig()));
    connect(ui->mehet2, SIGNAL(clicked()), this, SLOT(ResizeSmall()));
    connect(ui->nemkerek, SIGNAL(clicked()), this, SLOT(BankJon()));
    this->resize(420,90);
    this->setMaximumHeight(90);
    this->setMinimumHeight(90);
    this->setMaximumWidth(420);
    this->setMaximumWidth(420);


}

MainWindow::~MainWindow()
{
    delete ui;
}

Lap kettes("2", 2), harmas("3", 3), negyes("4", 4), otos("5", 5), hatos("6", 6), hetes("7", 7), nyolcas("8", 8), kilences("9", 9), tizes("10", 10), J("J", 10), Q("Q", 10), K("K", 10), A("A", 11);
vector<Lap> lapok{ kettes,harmas,negyes,otos,hatos,hetes,nyolcas,kilences,tizes,J,Q,K,A };
vector<Lap> bank, player, pakli;
int banksz = 0, playersz = 0, pakliszam = 1;
double  nyerek=0, vesztek=0, dontetlen=0;
bool pblackjack = false, bblackjack = false, ment=false;

void MainWindow::BankJon()
{
    while (banksz < 17)
    {
        QString ertek=Huzas(pakli, bank, banksz);
        if(Keres("bank")!=NULL)
            {
                Keres("bank")->setVisible(true);
                Keres("bank")->setText(ertek);
            }
        ui->bankertek->setText(QString::number(banksz));
        if (banksz == 21 && bank.size() == 2)
        {
            ui->bankertek->setText("BLACKJACK!");
            bblackjack = true;
        }
        else if (banksz > 21)
        {
            if (Aszkereso(bank)) banksz -= 10;
        }
    }
    ui->nyersz->clear();
    ui->dontetlen->clear();
    ui->nyersz2->clear();
    ui->dontetlen2->clear();
    Eredmeny();
}

void MainWindow::ResizeBig()
{
    this->resize(750,740);
    this->setMaximumHeight(740);
    this->setMinimumHeight(740);
    this->setMaximumWidth(750);
    this->setMinimumWidth(750);
    QDesktopWidget widget;
    QRect screenGeometry = widget.screenGeometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    this->move(-10000,-10000);
    this->move((width - this->width()) / 2.0,(height - this->height()) / 2.0);
    ui->blap->setVisible(true);
    ui->hasznalt->setVisible(false);
    ui->paklik->setVisible(false);
    ui->mehet->setVisible(false);

    srand(time(NULL));
    pakliszam=ui->paklik->value();

    Pakli(lapok, pakli, pakliszam);
    /*
    string teszt;
    for (int i=0;i<pakli.size();i++)
    {
        teszt+=pakli[i].szim;
    }
    ui->mentoov->setText(QString::fromStdString(teszt));
    */
    ui->bank1->setText(Huzas(pakli, bank, banksz));
    ui->bank1->setVisible(true);
    ui->bankertek->setText(QString::number(banksz));
    ui->player1->setText(Huzas(pakli, player, playersz));
    ui->player1->setVisible(true);
    ui->player2->setText(Huzas(pakli, player, playersz));
    ui->player2->setVisible(true);
    if (playersz == 22)
    {
        if(Aszkereso(player))
        playersz-=10;
    }
    if (playersz == 21)
    {
        ui->jatekosertek->setText("BLACKJACK!");
        pblackjack = true;
        BankJon();
        return;
    }
    else
    {
        ui->jatekosertek->setText(QString::number(playersz));
        ui->szazalek->setText(Valseg(pakli, player, playersz, ment));
        if(ment==true) ui->mentoov->setText("De van mentőőved!");
        ment=false;
}
    ui->mehet2->setVisible(false);
    ui->kerek->setVisible(true);
    ui->nemkerek->setVisible(true);
    ui->hny->setVisible(true);
    ui->hd->setVisible(true);
    ui->nyersz->setVisible(true);
    ui->dontetlen->setVisible(true);
    ui->hny2->setVisible(true);
    ui->hd2->setVisible(true);
    ui->nyersz2->setVisible(true);
    ui->dontetlen2->setVisible(true);
    ui->holallszmeg->setVisible(true);
    ui->megall->setVisible(true);
    ui->szamolas->setVisible(true);
    ui->annakazeselye->setVisible(true);
}

void MainWindow::ResizeSmall()
{
    this->setMaximumHeight(90);
    this->setMinimumHeight(90);
    this->setMaximumWidth(420);
    this->setMinimumWidth(420);
    this->resize(420,90);
    QDesktopWidget widget;
    QRect screenGeometry = widget.screenGeometry();
    int height = screenGeometry.height();
    int width = screenGeometry.width();
    this->move(-10000,-10000);
    this->move((width - this->width()) / 2.0,(height - this->height()) / 2.0);
    ui->blap->setVisible(false);
    ui->hasznalt->setVisible(true);
    ui->paklik->setVisible(true);
    ui->mehet->setVisible(true);
    ui->eredmeny->clear();
    bank.clear();
    player.clear();
    pakli.clear();
    banksz = 0, playersz = 0, pakliszam = 1;
    pblackjack = false, bblackjack = false, ment=false;
    ui->mentoov->clear();
    ui->bank1->setVisible(false);
    ui->bank2->setVisible(false);
    ui->bank3->setVisible(false);
    ui->bank4->setVisible(false);
    ui->bank5->setVisible(false);
    ui->bank6->setVisible(false);
    ui->player1->setVisible(false);
    ui->player2->setVisible(false);
    ui->player3->setVisible(false);
    ui->player4->setVisible(false);
    ui->player5->setVisible(false);
    ui->player6->setVisible(false);
    ui->bank1->clear();
    ui->bank2->clear();
    ui->bank3->clear();
    ui->bank4->clear();
    ui->bank5->clear();
    ui->bank6->clear();
    ui->player1->clear();
    ui->player2->clear();
    ui->player3->clear();
    ui->player4->clear();
    ui->player5->clear();
    ui->player6->clear();

}

QLabel* MainWindow::Keres(string def)
{
    if (def=="bank")
        {
            if (ui->bank2->text().isEmpty()) return ui->bank2;
            else if (ui->bank3->text().isEmpty()) return ui->bank3;
            else if (ui->bank4->text().isEmpty()) return ui->bank4;
            else if (ui->bank5->text().isEmpty()) return ui->bank5;
            else if (ui->bank6->text().isEmpty()) return ui->bank6;
        }
    else if (def=="player")
        {
            if (ui->player3->text().isEmpty()) return ui->player3;
            else if (ui->player4->text().isEmpty()) return ui->player4;
            else if (ui->player5->text().isEmpty()) return ui->player5;
            else if (ui->player6->text().isEmpty()) return ui->player6;
        }
    return NULL;
}


void MainWindow::on_kerek_clicked()
{
    QString ertek=Huzas(pakli, player, playersz);
    if(Keres("player")!=NULL)
        {
            Keres("player")->setVisible(true);
            Keres("player")->setText(ertek);
        }
    ui->jatekosertek->setText(QString::number(playersz));
    if (playersz > 21)
    {
        if (Aszkereso(player))
        {
            playersz -= 10;
            ui->jatekosertek->setText(QString::number(playersz));
            ui->mentoov->clear();
        }
        else
        {
            BankJon();
            return;
        }
    }
    if (playersz == 21)
    {
        BankJon();
        return;
    }
    ui->szazalek->setText(Valseg(pakli, player, playersz, ment));
    if(ment==true) ui->mentoov->setText("De van mentőőved!");
    ment=false;
    ui->nyersz->clear();
    ui->dontetlen->clear();
    ui->nyersz2->clear();
    ui->dontetlen2->clear();

}


void MainWindow::Eredmeny()
{
    if (bblackjack == false) ui->bankertek->setText(QString::number(banksz));

    if (banksz > 21 && playersz < 22) ui->eredmeny->setText("Nyertél!");
    else if (banksz < 22 && playersz > 21) ui->eredmeny->setText("Vesztettél!");
    else if (banksz > 21 && playersz > 21) ui->eredmeny->setText("Döntetlen!");
    else if (playersz < banksz) ui->eredmeny->setText("Vesztettél!");
    else if (playersz > banksz) ui->eredmeny->setText("Nyertél!");
    else if (playersz == banksz)
    {
        if (bblackjack == false && pblackjack == true) ui->eredmeny->setText("Nyertél!");
        else if (bblackjack == true && pblackjack == false) ui->eredmeny->setText("Vesztettél!");
        else ui->eredmeny->setText("Döntetlen!");
    }
    ui->eredmeny->setVisible(true);
    ui->kerek->setVisible(false);
    ui->nemkerek->setVisible(false);
    ui->hny->setVisible(false);
    ui->hd->setVisible(false);
    ui->nyersz->setVisible(false);
    ui->dontetlen->setVisible(false);
    ui->hny2->setVisible(false);
    ui->hd2->setVisible(false);
    ui->nyersz2->setVisible(false);
    ui->dontetlen2->setVisible(false);
    ui->holallszmeg->setVisible(false);
    ui->megall->setVisible(false);
    ui->szamolas->setVisible(false);
    ui->mehet2->setVisible(true);
    ui->szazalek->clear();
    ui->annakazeselye->setVisible(false);
    if (ui->eredmeny->text()=="Nyertél!") ui->eredmeny->setStyleSheet("QLabel {color : green;} ");
    if (ui->eredmeny->text()=="Vesztettél!") ui->eredmeny->setStyleSheet("QLabel {color : red;} ");
    if (ui->eredmeny->text()=="Döntetlen!") ui->eredmeny->setStyleSheet("QLabel {color : black;} ");
}


void Kiertekeles(int psz, int bsz, double mod)
{
    if (bsz>21 && psz<22) nyerek+=mod;
    else if (bsz<22 && psz>21) vesztek+=mod;
    else if (bsz>21 && psz>21) dontetlen+=mod;
    else if (bsz<psz) nyerek+=mod;
    else if (psz<bsz) vesztek+=mod;
    else if (psz=bsz) dontetlen+=mod;
}

void BSzim(vector<Lap> pak, int psz, vector<Lap> bk, int bsz, double mod)
{
    int psize=0;
    for(int i=0;i<pak.size();i++)
    {
        if(pak[i].volt==false) psize+=1;
    }
    mod=mod/psize;
    vector<Lap> bvecstart=bk, pakstart=pak;
    int bszstart=bsz;
    for(int i=0;i<pak.size();i++)
    {
        if(pak[i].volt==false)
        {
            bsz+=pak[i].ertek;
            bk.push_back(pak[i]);
            pak[i].volt=true;
            if (bsz<17) BSzim(pak,psz,bk,bsz,mod);
            else if (bsz>=17 && bsz<22)
            {
                if (bk.size()==2 && bsz==21) vesztek+=mod;
                else Kiertekeles(psz,bsz,mod);
            }
            else if (bsz>21)
                {
                    if(Aszkereso(bk))
                    {
                        bsz-=10;
                        if (bsz<17) BSzim(pak,psz,bk,bsz,mod);
                        else Kiertekeles(psz,bsz,mod);
                    }
                    else Kiertekeles(psz,bsz,mod);
                }

        }
        bk=bvecstart;
        bsz=bszstart;
        pak=pakstart;

    }
}



void PSzim(vector<Lap> pak, vector<Lap> pl, int psz, vector<Lap> bk, int bsz, int megall, double mod)
{
    int psize=0;
    for(int i=0;i<pak.size();i++)
    {
        if(pak[i].volt==false) psize+=1;
    }
    mod=mod/psize;
    vector<Lap> pvecstart=pl, pakstart=pak;
    int pszstart=psz;
    for(int i=0;i<pak.size();i++)
    {
        if(pak[i].volt==false)
        {
            psz+=pak[i].ertek;
            pl.push_back(pak[i]);
            pak[i].volt=true;
            if (psz<megall) PSzim(pak,pl,psz,bk, bsz,megall,mod);
            else if (psz>=megall && psz<22) BSzim(pak,psz,bk,bsz,mod);
            else if (psz>21)
                {
                    if(Aszkereso(pl))
                    {
                        psz-=10;
                        if (psz<megall) PSzim(pak,pl,psz,bk,bsz,megall,mod);
                        else BSzim(pak,psz,bk,bsz,mod);
                    }
                    else BSzim(pak,psz,bk,bsz,mod);
                }

        }
        pl=pvecstart;
        psz=pszstart;
        pak=pakstart;

    }
}


void MainWindow::on_szamolas_clicked()
{
    int megall=ui->megall->value();
    PSzim(pakli,player,playersz,bank,banksz,megall,1);
    ui->nyersz->setText(QString::fromStdString(to_string((nyerek/(nyerek+dontetlen+vesztek))*100))+"%");
    ui->dontetlen->setText(QString::fromStdString(to_string((dontetlen/(nyerek+dontetlen+vesztek))*100))+"%");
    nyerek=0;
    vesztek=0;
    dontetlen=0;
    BSzim(pakli,playersz,bank,banksz,1);
    ui->nyersz2->setText(QString::fromStdString(to_string((nyerek/(nyerek+dontetlen+vesztek))*100))+"%");
    ui->dontetlen2->setText(QString::fromStdString(to_string((dontetlen/(nyerek+dontetlen+vesztek))*100))+"%");
    nyerek=0;
    vesztek=0;
    dontetlen=0;
}

