#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    auto size = vector_model_.items.size();
    ui -> pb_pop_back -> setDisabled(!size);
    QString txt = "%1";
    txt = txt.arg(size);
    ui ->txt_size -> setText(txt);
    ui ->list_widget ->clear();
    if (size)
        ShowVector();

}

void MainWindow::ShowVector(){

    QStringList list;
    for (size_t i = 0; i < vector_model_.items.size(); ++i){
        QString txt = "%1: ";
        list <<txt.arg(i) + QString::fromStdString(vector_model_.items[i]);

    }
    ui -> list_widget ->addItems(list);

}

void MainWindow::on_pb_pop_back_clicked(){
    vector_model_.items.pop_back();
    ApplyModel();
}


void MainWindow::on_pb_push_back_clicked(){
    std::string txt = ui -> txt_elem_content -> text().toStdString();
    vector_model_.items.push_back(txt);
    ApplyModel();
}


void MainWindow::on_pb_clear_clicked(){
    vector_model_.items.clear();
    ApplyModel();
}


void MainWindow::on_pb_days_clicked(){
    vector_model_.items = {"Понедельник", "Вторник","Среда","Четверг","Пятница","Суббота","Воскресенье"};
    ApplyModel();
}


void MainWindow::on_pb_months_clicked(){
    vector_model_.items = {"Январь","Февраль","Март","Апрель","Май"
    ,"Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"};
    ApplyModel();
}

