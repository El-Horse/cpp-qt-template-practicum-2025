#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #include "controller.h"
// #include "game.h"
// #include "qevent.h"
// #include "qdebug.h"
// #include "qlogging.h"
#include "character.h"
#include "characters.h"
#include "context.h"
#include "controller.h"

#include <QMainWindow>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Game& game, Controller& controller,
               QWidget *parent = nullptr);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event) override {
        if (event->isAutoRepeat()) {
            return QWidget::keyPressEvent(event);
        }
        switch (event->key()) {
        case Qt::Key_Right:
            game_.GetPlayer().SetDirection(Direction::kRight);
            break;
        case Qt::Key_Left:
            game_.GetPlayer().SetDirection(Direction::kLeft);
            break;
        case Qt::Key_Up:
            game_.GetPlayer().SetDirection(Direction::kUp);
            break;
        case Qt::Key_Down:
            game_.GetPlayer().SetDirection(Direction::kDown);
            break;
        // Здесь обрабатываются различные клавиши.

        default:
            QWidget::keyPressEvent(event); // call base class implementation
        }
    }
private:
    Ui::MainWindow *ui;
    Game& game_;
};
#endif // MAINWINDOW_H
