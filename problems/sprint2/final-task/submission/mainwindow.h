#pragma once

#include "calculator.h"


#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum class Operation{
    NO_OPERATION,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    POWER
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void SetText (const QString& text);
    void AddText (const QString& text);
    QString RemoveTrailingZeroes(const QString &text);
    QString NormalizeNumber(const QString &text);
    void SetOperation (Operation op);
    QString OpToString(Operation op) const;

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
    void on_btn_dot_clicked();
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

private:
    Ui::MainWindow* ui;
    Calculator calculator_;
    QString input_number_;
    double active_number_ = 0;
    Operation current_operation_ = Operation::NO_OPERATION;
    bool has_memory = false;
    double memory = 0;
};
