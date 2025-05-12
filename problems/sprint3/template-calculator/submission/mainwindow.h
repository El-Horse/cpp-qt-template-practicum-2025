#pragma once

#include "calculator.h"
#include "enums.h"
#include <string>
#include <QMainWindow>
// Реальзуйте класс главного окна.

#pragma once



#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void SetInputText (const std::string& text); //переписать
    void SetErrorText(const std::string& text);
    void SetFormulaText(const std::string& text);
    void SetMemText(const std::string& text);
    void SetExtraKey(const std::optional<std::string>& key);



    void SetDigitKeyCallback(std::function<void(int key)> cb){
        digit_cb_ = cb;
    }
    void SetProcessOperationKeyCallback(std::function<void(Operation key)> cb){
        operation_cb_ = cb;
    }
    void SetProcessControlKeyCallback(std::function<void(ControlKey key)> cb){
        control_cb_ = cb;
    }
    void SetControllerCallback(std::function<void(ControllerType controller)> cb){
        controller_cb_ = cb;
    }


private slots:

    void on_btn_0_clicked();
    void on_btn_1_clicked();
    void on_bnt_2_clicked();
    void on_btn_3_clicked();
    void on_btn_4_clicked();
    void on_btn_5_clicked();
    void on_btn_6_clicked();
    void on_btn_7_clicked();
    void on_btn_8_clicked();
    void on_btn_9_clicked();
    void on_tb_extra_clicked();
    void on_btn_invert_clicked();
    void on_btn_delite_clicked();
    void on_btn_plus_clicked();
    void on_btn_minus_clicked();
    void on_btn_multiply_clicked();
    void on_btn_divide_clicked();
    void on_btn_pow_clicked();
    void on_btn_clear_clicked();
    void on_btn_result_clicked();
    void on_btn_mem_clear_clicked();
    void on_btn_mem_read_clicked();
    void on_btn_mem_save_clicked();

    void on_cmb_controller_currentIndexChanged(int index);



private:
    Ui::MainWindow* ui;
    // Calculator<Number> calculator_;
    QString input_number_;
    // Number active_number_ = 0;
    Operation current_operation_;
//    bool number_is_set_ = false;

    std::function<void(Operation key)> operation_cb_;
    std::function<void(int key)> digit_cb_;
    std::function<void(ControlKey key)> control_cb_;
    std::function<void(ControllerType controller)> controller_cb_;



};
