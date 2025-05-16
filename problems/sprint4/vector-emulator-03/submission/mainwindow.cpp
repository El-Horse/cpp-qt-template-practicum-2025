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
    ApplyIterator();
    // CheckButtons();

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {

    auto size = vector_model_.items.size();
    vector_model_.iterator = vector_model_.items.begin();
    auto iter = vector_model_.iterator - vector_model_.items.begin();
    ui -> pb_pop_back -> setDisabled(!size);
    QString txt = "%1";
    txt = txt.arg(size);
    ui ->txt_size -> setText(txt);


    ui ->list_widget ->clear();

    std::string s = std::to_string(vector_model_.items.capacity());
    ui->txt_capacity->setText(QString::fromStdString(s));

    ShowVector();

    vector_model_.iterator = vector_model_.items.begin() + iter;
    CheckButtons();
}

void MainWindow::ApplyIterator(){

    int index = std::distance(vector_model_.items.begin(), vector_model_.iterator);
    ui -> list_widget -> setCurrentRow(index);
    if (!vector_model_.items.empty())
        ui->txt_elem_content->setText(QString::fromStdString(vector_model_.items[index]));
    else
        ui->txt_elem_content->clear();
    CheckButtons();

}

void MainWindow::ShowVector(){

    QStringList list;
    for (size_t i = 0; i < vector_model_.items.size(); ++i){
        QString txt = "%1: ";
        list <<txt.arg(i) + QString::fromStdString(vector_model_.items[i]);

    }
    list <<"end";
    ui -> list_widget ->addItems(list);

}

void MainWindow::CheckButtons() const
{
    if (vector_model_.items.empty()){
        ui -> pb_minus -> setDisabled(true);
        ui -> pb_plus -> setDisabled(true);
        ui->pb_edit->setDisabled(true);
        ui->pb_erase->setDisabled(true);
    }

    else if (vector_model_.iterator == vector_model_.items.begin()){
        ui -> pb_minus -> setDisabled(true);
        ui -> pb_plus -> setDisabled(false);
        ui->pb_edit->setDisabled(false);
        ui->pb_erase->setDisabled(false);
    }
    else if (vector_model_.iterator == vector_model_.items.end()){
        ui -> pb_plus -> setDisabled(true);
        ui -> pb_minus -> setDisabled(false);
        ui->pb_edit->setDisabled(true);
        ui->pb_erase->setDisabled(true);

    }
    else{
        ui -> pb_minus -> setDisabled(false);
        ui -> pb_plus -> setDisabled(false);
        ui->pb_edit->setDisabled(false);
        ui->pb_erase->setDisabled(false);
    }
}

void MainWindow::on_pb_pop_back_clicked(){
    vector_model_.items.pop_back();
    ApplyModel();
    ApplyIterator();
}


void MainWindow::on_pb_push_back_clicked(){
    std::string txt = ui -> txt_elem_content -> text().toStdString();
    vector_model_.items.push_back(txt);
    ApplyModel();
    ApplyIterator();
}


void MainWindow::on_pb_clear_clicked(){
    vector_model_.items.clear();
    ApplyModel();
    ApplyIterator();
}


void MainWindow::on_pb_days_clicked(){
    vector_model_.items = {"Понедельник", "Вторник","Среда","Четверг","Пятница","Суббота","Воскресенье"};
    ApplyModel();
    ApplyIterator();
}


void MainWindow::on_pb_months_clicked(){
    vector_model_.items = {"Январь","Февраль","Март","Апрель","Май"
                           ,"Июнь","Июль","Август","Сентябрь","Октябрь","Ноябрь","Декабрь"};
    ApplyModel();
    ApplyIterator();
}


void MainWindow::on_pb_edit_clicked(){
    auto it = vector_model_.iterator - vector_model_.items.begin();

    std::string txt = ui->txt_elem_content->text().toStdString();
    *vector_model_.iterator = txt;

    ApplyModel();
    ui->list_widget->setCurrentRow(it);
    vector_model_.iterator = vector_model_.items.begin() + it;
}


void MainWindow::on_pb_erase_clicked(){
    auto iter = vector_model_.items.erase(vector_model_.iterator);
    vector_model_.iterator = iter;
    ApplyModel();
    ApplyIterator();
    CheckButtons();
}


void MainWindow::on_pb_insert_clicked(){
    auto txt = ui->txt_elem_content->text().toStdString();
    vector_model_.items.insert(vector_model_.iterator,txt);
    ApplyModel();
    ApplyIterator();
    CheckButtons();
}


void MainWindow::on_pb_minus_clicked(){
    if (vector_model_.iterator != vector_model_.items.begin()){
        --vector_model_.iterator;
        ApplyIterator();
    }
    CheckButtons();
}


void MainWindow::on_pb_plus_clicked(){
    if (vector_model_.iterator != vector_model_.items.end()){
        ++vector_model_.iterator;
        ApplyIterator();
    }
    CheckButtons();
}


void MainWindow::on_pb_begin_clicked(){
    vector_model_.iterator = vector_model_.items.begin();
    ApplyIterator();
    CheckButtons();
}


void MainWindow::on_pb_end_clicked(){
    vector_model_.iterator = vector_model_.items.end();
    ApplyIterator();
    CheckButtons();
}

void MainWindow::on_list_widget_currentRowChanged(int currentRow)
{

    currentRow < 0? currentRow = 0 : currentRow *= 1;
    if (!vector_model_.items.empty()){

        vector_model_.iterator = vector_model_.items.begin() + currentRow;
        ui->txt_elem_content->setText(QString::fromStdString(vector_model_.items[currentRow]));
    }
    CheckButtons();
}


void MainWindow::on_pb_reserve_clicked(){
    size_t s = ui->txt_capacity->text().toInt();
    vector_model_.items.reserve(s);
}


void MainWindow::on_pb_resize_clicked(){
    size_t s = ui->txt_size->text().toInt();
    vector_model_.items.resize(s);
    ApplyModel();
    ApplyIterator();
    CheckButtons();
}

