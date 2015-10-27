#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton* btn_aufgabe1 = findChild<QPushButton*>("btn_aufgabe1");
    QObject::connect(btn_aufgabe1, SIGNAL (clicked()), this, SLOT (executeAufgabe1()));

    QPushButton* btn_aufgabe2a = findChild<QPushButton*>("btn_aufgabe2a");
    QPushButton* btn_aufgabe2b = findChild<QPushButton*>("btn_aufgabe2b");
    QPushButton* btn_aufgabe2c = findChild<QPushButton*>("btn_aufgabe2c");
    QPushButton* btn_aufgabe2d = findChild<QPushButton*>("btn_aufgabe2d");
    QPushButton* btn_aufgabe3 = findChild<QPushButton*>("btn_aufgabe3");
    QPushButton* btn_aufgabe4 = findChild<QPushButton*>("btn_aufgabe4");
    QObject::connect(btn_aufgabe2a, SIGNAL (clicked()), this, SLOT (executeAufgabe2a()));
    QObject::connect(btn_aufgabe2b, SIGNAL (clicked()), this, SLOT (executeAufgabe2b()));
    QObject::connect(btn_aufgabe2c, SIGNAL (clicked()), this, SLOT (executeAufgabe2c()));
    QObject::connect(btn_aufgabe2d, SIGNAL (clicked()), this, SLOT (executeAufgabe2d()));
    QObject::connect(btn_aufgabe3, SIGNAL (clicked()), this, SLOT (executeAufgabe3()));
    QObject::connect(btn_aufgabe4, SIGNAL (clicked()), this, SLOT (executeAufgabe4()));


    QPushButton* btn_exit = findChild<QPushButton*>("btn_exit");
    QObject::connect(btn_exit, SIGNAL(clicked()), this, SLOT(exit()));


    //    qDebug() << "MainWindow: " << "btn @ " << btn_aufgabe1;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit()
{
    this->close();
}


void MainWindow::executeAufgabe1()
{
    ChallangeOne co(this);

    string filename = "Images/Aufgabe1/aufgabe_1.jpg";
    string resultPath = "Images/Aufgabe1/Results/";

    co.start(filename, resultPath);
    co.exec();
}

void MainWindow::executeAufgabe2a()
{
    ChallangeTwo co(this);

    string filename = "Images/Aufgabe2/aufgabe_2.jpg";
    string resultPath = "Images/Aufgabe2/Results/a/";

    co.startA(filename, resultPath);
    co.exec();
}

void MainWindow::executeAufgabe2b()
{
    ChallangeTwo co(this);

    string filename = "Images/Aufgabe2/aufgabe_2.jpg";
    string resultPath = "Images/Aufgabe2/Results/b/";

    co.startB(filename, resultPath);
    co.exec();
}

void MainWindow::executeAufgabe2c()
{
    ChallangeTwo co(this);

    string filename = "Images/Aufgabe2/aufgabe_2.jpg";
    string resultPath = "Images/Aufgabe2/Results/c/";

    co.startC(filename, resultPath);
    co.exec();
}

void MainWindow::executeAufgabe2d()
{
    ChallangeTwo co(this);

    string filename = "Images/Aufgabe2/aufgabe_2.jpg";
    string resultPath = "Images/Aufgabe2/Results/d/";

    co.startD(filename, resultPath);
    co.exec();
}

void MainWindow::executeAufgabe3()
{
    string filename = "Images/Aufgabe3/aufgabe_3.jpg";
    string resultPath = "Images/Aufgabe3/Results/";
    ChallangeThree co(filename, resultPath, this);

    co.exec();
}

void MainWindow::executeAufgabe4()
{
    string filename = "Images/Aufgabe4/aufgabe_4.jpg";
    string resultPath = "Images/Aufgabe4/Results/";

    ChallangeFour co(filename, resultPath, true);
    co.exec();
}


