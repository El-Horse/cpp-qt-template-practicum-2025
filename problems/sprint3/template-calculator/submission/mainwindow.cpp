// Реальзуйте класс главного окна.
// edit 2

#include "mainwindow.h"
#include "controller.h"
#include "ui_mainwindow.h"
#include "rational.h"
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

// QString MainWindow::OpToString(Operation op) const  {
//     switch(op) {
//     // case Operation::NO_OPERATION: return "";
//     case Operation::ADDITION: return "+";
//     case Operation::DIVISION: return "÷";
//     case Operation::MULTIPLICATION: return "×";
//     case Operation::SUBTRACTION: return "−";
//     case Operation::POWER: return "^";
//     default: return "";
//     }
// }

// QString MainWindow::RemoveTrailingZeroes(const QString &text) {
//     for (qsizetype i = 0; i < text.size(); ++i) {
//         if (text[i] != '0') {
//             return text.mid(i);
//         }
//     }
//     return "";
// }

// QString MainWindow::NormalizeNumber(const QString &text) {
//     if (text.isEmpty()) {
//         return "0";
//     }
//     if (text.startsWith('.')) {
//         // Рекурсивный вызов.
//         return NormalizeNumber("0" + text);
//     }
//     if (text.startsWith('-')) {
//         // Рекурсивный вызов.
//         return "-" + NormalizeNumber(text.mid(1));
//     }
//     if (text.startsWith('0') && !text.startsWith("0.")) {
//         return NormalizeNumber(RemoveTrailingZeroes(text));
//     }
//     return text;
// }

// void MainWindow::SetText(const QString &text =""){
//     input_number_ = NormalizeNumber(text);
//     active_number_ = input_number_.toDouble();

//     ui -> l_result -> setText(input_number_);
// }

// void MainWindow::AddText(const QString& text){
// //    SetText(input_number_ += text);
// }



// void MainWindow::SetOperation(Operation op){
//     QString text = ("%1 %2");
//     current_operation_ = op;

//     if(number_is_set_){
//         text = text.arg(calculator_.Get()).arg(OpToString(current_operation_));
//         ui -> l_formula -> setText(text);
//         return;
//     }


//     calculator_.Set(active_number_);

//     if(current_operation_ != Operation::NO_OPERATION) {

//         text = text.arg(active_number_).arg(OpToString(current_operation_));
//         ui -> l_formula -> setText(text);
//         input_number_ = "";
//         ui -> l_result -> setText("0");
//         number_is_set_ = true;
//     }


// }

// Обработка нажатия кнопок
void MainWindow::on_btn_0_clicked(){digit_cb_(0);}

void MainWindow::on_btn_1_clicked(){digit_cb_(1);}

void MainWindow::on_bnt_2_clicked(){digit_cb_(2);}

void MainWindow::on_btn_3_clicked(){digit_cb_(3);}
void MainWindow::on_btn_4_clicked(){digit_cb_(4);}

void MainWindow::on_btn_5_clicked(){digit_cb_(5);}

void MainWindow::on_btn_6_clicked(){digit_cb_(6);}

void MainWindow::on_btn_7_clicked(){digit_cb_(7);}

void MainWindow::on_btn_8_clicked(){digit_cb_(8);};

void MainWindow::on_btn_9_clicked(){digit_cb_(9);}

void MainWindow::on_btn_plus_clicked(){operation_cb_(Operation::ADDITION);}

void MainWindow::on_btn_minus_clicked(){operation_cb_(Operation::SUBTRACTION);}

void MainWindow::on_btn_multiply_clicked(){operation_cb_(Operation::MULTIPLICATION);}

void MainWindow::on_btn_divide_clicked(){operation_cb_(Operation::DIVISION);}

void MainWindow::on_btn_pow_clicked(){operation_cb_(Operation::POWER);}

void MainWindow::on_tb_extra_clicked(){control_cb_(ControlKey::EXTRA_KEY);}

void MainWindow::on_btn_invert_clicked(){control_cb_(ControlKey::PLUS_MINUS);}

void MainWindow::on_btn_delite_clicked(){control_cb_(ControlKey::BACKSPACE);}

void MainWindow::on_btn_clear_clicked(){control_cb_(ControlKey::CLEAR);}

void MainWindow::on_btn_result_clicked(){control_cb_(ControlKey::EQUALS);}

void MainWindow::on_btn_mem_clear_clicked(){control_cb_(ControlKey::MEM_CLEAR);}

void MainWindow::on_btn_mem_read_clicked(){control_cb_(ControlKey::MEM_LOAD);}

void MainWindow::on_btn_mem_save_clicked(){control_cb_(ControlKey::MEM_SAVE);}

void MainWindow::on_cmb_controller_currentIndexChanged(int){
    auto t = static_cast<ControllerType>( ui -> cmb_controller -> currentIndex());
    controller_cb_ (t);
}

// обработка кнопок ^^^^^
// Методы:

void MainWindow::SetInputText (const std::string& text){
    ui -> l_result -> setStyleSheet("");
    ui -> l_result -> setText(QString::fromStdString(text));
}
void MainWindow::SetErrorText(const std::string& text){
    ui -> l_result -> setStyleSheet("color: red;");
    ui -> l_result -> setText(QString::fromStdString(text));
}
void MainWindow::SetFormulaText(const std::string& text){
    ui -> l_formula -> setText(QString::fromStdString(text));
}
void MainWindow::SetMemText(const std::string& text){
    ui -> l_memory -> setText(QString::fromStdString(text));
}
void MainWindow::SetExtraKey(const std::optional<std::string>& key){
    ui -> tb_extra -> setEnabled(key.has_value());
    ui -> tb_extra -> setText(QString::fromStdString(key.value()));
}







