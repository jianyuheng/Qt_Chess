#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}



MainWindow::~MainWindow()
{
    delete ui;
}

//用FEN串格式保存棋局
void MainWindow::on_actionSave_triggered()
{

}

//打开保存的FEN串格式棋局
void MainWindow::on_actionOpen_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("加载棋局"),QString(),tr("All Files(*);;Text Files(*.txt)"));
}


//关于 copyright
void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this,tr("关于"),tr("copyright:    jyheng2017"));
}


//开始游戏
void MainWindow::on_actionStart_triggered()
{

}
