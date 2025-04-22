#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QLabel>
#include <QString>
#include <QDir>

#include <F:\_cpp\cpp-qt-template-practicum-2025\mocks_library\prac\QTimer>
#include <F:\_cpp\cpp-qt-template-practicum-2025\mocks_library\prac\QFileDialog>



QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetPixmap(const QString path) {
        active_pixmap = QPixmap(path);
    }

    void FitImage();
    void SetFolder(const QString& new_folder);

    QString GetCurrentFile ();
    // void SetFolder(const QDir& path){
    //     current_folder_ = path;
    //     cur_file_index_ = 0;

    // }
private slots:
    void on_btn_left_clicked();

    void on_btn_right_clicked();

    // Назовём слот slotCustomMenuRequested, чтобы показать,
    // что это реация на вызов меню.
    void slotCustomMenuRequested(QPoint pos) {
        // Метод ui->menu->popup открывает меню в заданном месте.
        // Используем метод mapToGlobal, чтобы преобразовать
        // координаты точки на форме в координаты точки экрана.
        ui-> menu -> popup(this->mapToGlobal(pos));
    }

    // Слоты для нажатия кнопок
    void slotOnTop (bool);
    void slotSetResourceFolder(bool);
    void slotSetCustomFolder(bool);
    void slotClose(void);
    void slotSetDelay(void);
    void OnTimerTimeout(void);
    void slotDelay1(void);
    void slotDelay5(void);
    void slotDelay10(void);
    void slotDelayOff(void);

private:
    void resizeEvent(QResizeEvent *event) override;
//    QString img_path_ = ":cats/images/cat1.jpg";

private:
    Ui::MainWindow *ui;
    QPixmap active_pixmap;
    QLabel lbl_new_ {this};
    QString default_img_folder_ = ":cats/images/";
    QDir current_folder_;
    int cur_file_index_ = 0;
//    void UpdateEnabled();
    void UpdateImage(); // Обновление изображения
    QString SetCustomFolder(void);
    bool on_top_flag_ = true;
    QPixmap GetImageByPath(QString path) const;
    int period = 0;
    std::pair<QPixmap, int> FindNextImage(int start_index, int direction) const;
    prac::QTimer swith_timer_ {this};
    unsigned int delay_time_ = 0;

    void CheckIndex(bool direction);
};
#endif // MAINWINDOW_H
