// Реальзуйте класс главного окна.
// edit 2

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->l_result->setText("0");
    ui->l_memory->setText("");
    ui->l_formula->setText("");

}

MainWindow::~MainWindow() {
    delete ui;
}

QString MainWindow::OpToString(Operation op) const  {
    switch(op) {
    case Operation::NO_OPERATION: return "";
    case Operation::ADDITION: return "+";
    case Operation::DIVISION: return "÷";
    case Operation::MULTIPLICATION: return "×";
    case Operation::SUBTRACTION: return "−";
    case Operation::POWER: return "^";
    default: return "";
    }
}

QString MainWindow::RemoveTrailingZeroes(const QString &text) {
    for (qsizetype i = 0; i < text.size(); ++i) {
        if (text[i] != '0') {
            return text.mid(i);
        }
    }
    return "";
}

QString MainWindow::NormalizeNumber(const QString &text) {
    if (text.isEmpty()) {
        return "0";
    }
    if (text.startsWith('.')) {
        // Рекурсивный вызов.
        return NormalizeNumber("0" + text);
    }
    if (text.startsWith('-')) {
        // Рекурсивный вызов.
        return "-" + NormalizeNumber(text.mid(1));
    }
    if (text.startsWith('0') && !text.startsWith("0.")) {
        return NormalizeNumber(RemoveTrailingZeroes(text));
    }
    return text;
}

void MainWindow::SetText(const QString &text =""){
    input_number_ = NormalizeNumber(text);
    active_number_ = input_number_.toDouble();

    ui -> l_result -> setText(input_number_);
}

void MainWindow::AddText(const QString& text){
    SetText(input_number_ += text);
}



void MainWindow::SetOperation(Operation op){
    QString text = ("%1 %2");
    current_operation_ = op;

    if(number_is_set_){
        text = text.arg(calculator_.Get()).arg(OpToString(current_operation_));
        ui -> l_formula -> setText(text);
        return;
    }


    calculator_.Set(active_number_);

    if(current_operation_ != Operation::NO_OPERATION) {

        text = text.arg(active_number_).arg(OpToString(current_operation_));
        ui -> l_formula -> setText(text);
        input_number_ = "";
        ui -> l_result -> setText("0");
        number_is_set_ = true;
    }


}

// Обработка нажатия кнопок
void MainWindow::on_btn_0_clicked(){
    AddText("0");
}

void MainWindow::on_btn_1_clicked(){
    AddText("1");
}

void MainWindow::on_bnt_2_clicked(){
    AddText("2");
}

void MainWindow::on_btn_3_clicked(){
    AddText("3");
}

void MainWindow::on_btn_4_clicked(){
    AddText("4");
}

void MainWindow::on_btn_5_clicked(){
    AddText("5");
}

void MainWindow::on_btn_6_clicked(){
    AddText("6");
}

void MainWindow::on_btn_7_clicked(){
    AddText("7");
}

void MainWindow::on_btn_8_clicked(){
    AddText("8");
}

void MainWindow::on_btn_9_clicked(){
    AddText("9");
}

void MainWindow::on_btn_dot_clicked(){
    if (!input_number_.contains(".")){
        AddText(".");
    }
}

void MainWindow::on_btn_invert_clicked(){
    if(input_number_.startsWith("-")){
        SetText(input_number_.mid(1));
    }
    else{
        SetText(input_number_ = "-" + input_number_);
    }
}

void MainWindow::on_btn_delite_clicked(){
    if (input_number_ != "0"){
        input_number_.chop(1);
        SetText(input_number_);
    }
}

void MainWindow::on_btn_plus_clicked(){
    SetOperation(Operation::ADDITION);
}

void MainWindow::on_btn_minus_clicked(){
    SetOperation(Operation::SUBTRACTION);
}

void MainWindow::on_btn_multiply_clicked(){
    SetOperation(Operation::MULTIPLICATION);
}

void MainWindow::on_btn_divide_clicked(){
    SetOperation(Operation::DIVISION);
}

void MainWindow::on_btn_pow_clicked(){
    SetOperation(Operation::POWER);
}

void MainWindow::on_btn_clear_clicked(){
    current_operation_ = Operation::NO_OPERATION;
    ui -> l_formula ->clear();
    SetText();

}

void MainWindow::on_btn_result_clicked()
{
    if (current_operation_ == Operation::NO_OPERATION)
        return;
    QString text = "%1 %2 %3 =";
    text = text.arg(calculator_.Get()).arg(OpToString(current_operation_)).arg(active_number_);
    ui -> l_formula -> setText(text);
    active_number_ = calculator_.Calculate(OpToString(current_operation_), active_number_);

    SetText(QString::number(active_number_));

    input_number_ = QString::number(active_number_);
    current_operation_ = Operation::NO_OPERATION;
    number_is_set_ = false;
}



void MainWindow::on_btn_mem_clear_clicked(){
    has_memory = false;
    ui -> l_memory -> clear();
}

void MainWindow::on_btn_mem_read_clicked(){
    if(!has_memory)
        return;

    active_number_ = memory;
    input_number_ = QString::number(active_number_);
    ui -> l_result -> setText(input_number_);
}

void MainWindow::on_btn_mem_save_clicked(){
    has_memory = true;
    memory = active_number_;
    ui -> l_memory -> setText("M");
    input_number_ = "";
}
