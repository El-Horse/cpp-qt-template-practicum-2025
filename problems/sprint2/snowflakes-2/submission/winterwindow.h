#ifndef WINTERWINDOW_H
#define WINTERWINDOW_H

#include <QMainWindow>
#include <prac/QPainter>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui {
class WinterWindow;
}
QT_END_NAMESPACE

struct Vector2D {
    double x;
    double y;
};

struct Point2D {
    double x;
    double y;
};

inline Vector2D RotateVector(Vector2D src, double angle) {
    double a_rad = angle / 180. * M_PI;
    double sin_v = std::sin(a_rad);
    double cos_v = std::cos(a_rad);
    return Vector2D{
        src.x * cos_v + src.y * sin_v, - src.x * sin_v + src.y * cos_v
    };
}

inline Vector2D Add(Vector2D l, Vector2D r) {
    return Vector2D{l.x + r.x, l.y + r.y};
}

inline Point2D Add(Point2D l, Vector2D r) {
    return Point2D{l.x + r.x, l.y + r.y};
}

struct SnowFlakeParams {
    Point2D center;
    QColor color;
    double size;
    double line_width;
    double rotation;
    int depth;
    double scale_factor;
};

class SnowFlake {
public:
    SnowFlake(SnowFlakeParams params) : params_(params) {

    }

    void Draw(prac::QPainter& painter) const {
        // 1. Установите перо в painter. Нужно использовать цвет
        //    снежинки и толщину линии из переменной класса params_.
        // QPen line_pen {params_.color};
        // line_pen.setWidth(params_.line_width);
        painter.setPen(QPen(QBrush(params_.color), params_.line_width));
        //painter.setPen(line_pen);
        // 2. Разместите здесь код для рисования шести лучей на основе
        //    переменной params_ и метода DrawRotatedVector.
        //    Учтите центр снежинки – params_.center, длину вектора –
        //    params_.size.

        // QList<Point2D> points{};
        // int val = params_.depth;

        //     while (val > 0){
        //     for(int i =0; i < 6; ++i){
        //         points.push_back(DrawRotatedVector(painter,params_.center,(params_.rotation + 60*i),params_.size));
        //     }
        //         QList<Point2D> points_new{};
        //     int i =0;
        //         for (auto a : points){

        //             for (int var = 0; var < 6; ++var) {
        //                 points_new.push_back(DrawRotatedVector(painter,a,(params_.rotation + 60* var), params_.size * params_.scale_factor));

        //             }
        //         points[i] = points_new[i];
        //         ++i;
        //         }
        //         --val;
        //     }

        for(int i = 0; i < 6; ++i){
            auto flake_2 = GetNextLevelFlake(DrawRotatedVector(painter,params_.center,(params_.rotation + 60*i),params_.size));

            if (params_.depth > 0){
                for (int i = 0; i <6; ++i){
                    auto flake_3 = GetNextLevelFlake(DrawRotatedVector(painter,flake_2.params_.center,(params_.rotation + 60*i),flake_2.params_.size));
                    if (params_.depth > 1){
                        for (int i = 0; i <6; ++i){
                            auto flake_4 = GetNextLevelFlake(DrawRotatedVector(painter,flake_3.params_.center,(params_.rotation + 60*i),flake_3.params_.size));
                            if (params_.depth > 2){
                                for (int i = 0; i <6; ++i){
                                    auto flake_5 = GetNextLevelFlake(DrawRotatedVector(painter,flake_4.params_.center,(params_.rotation + 60*i),flake_4.params_.size));
                                    if (params_.depth > 3){
                                        for (int i = 0; i < 6; ++i){
                                            auto flake_6 = GetNextLevelFlake(DrawRotatedVector(painter,flake_5.params_.center,(params_.rotation + 60*i),flake_5.params_.size));
                                            if (params_.depth > 4){
                                            for (int i = 0; i < 6; ++i){
                                                    DrawRotatedVector(painter,flake_6.params_.center,(params_.rotation + 60*i),flake_6.params_.size);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }


        // for(int i = 0; i < 6; ++i){
        //     auto flake_1 = DrawRotatedVector(painter,params_.center,(params_.rotation + 60*i),params_.size);

        //     if (params_.depth > 0){
        //         auto new_flake_2 = GetNextLevelFlake(flake_1);
        //         for (int i = 0; i <6; ++i){
        //             auto flake_2 = DrawRotatedVector(painter,new_flake_2.params_.center,(new_flake_2.params_.rotation + 60*i),new_flake_2.params_.size);
        //             if (params_.depth > 1){
        //                 auto new_flake_3 = GetNextLevelFlake(flake_2);
        //                 for (int i = 0; i <6; ++i){
        //                     auto flake_3 = DrawRotatedVector(painter,new_flake_3.params_.center,(new_flake_3.params_.rotation + 60*i),new_flake_3.params_.size);
        //                     if (params_.depth > 2){
        //                         auto new_flake_4 = GetNextLevelFlake(flake_3);
        //                         for (int i = 0; i <6; ++i){
        //                             auto flake_4 = DrawRotatedVector(painter,new_flake_4.params_.center,(new_flake_4.params_.rotation + 60*i),new_flake_4.params_.size);
        //                             if (params_.depth > 3){
        //                                 auto new_flake_5 = GetNextLevelFlake(flake_4);
        //                                 for (int i = 0; i <6; ++i){
        //                                     auto flake_5 = DrawRotatedVector(painter,new_flake_5.params_.center,(new_flake_5.params_.rotation + 60*i),new_flake_5.params_.size);
        //                                     if (params_.depth > 4){
        //                                         auto new_flake_6 = GetNextLevelFlake(flake_5);
        //                                         for (int i = 0; i <6; ++i){
        //                                             DrawRotatedVector(painter,new_flake_6.params_.center,(new_flake_6.params_.rotation + 60*i),new_flake_6.params_.size);

        //                                         }
        //                                     }
        //                                 }
        //                             }
        //                         }
        //                     }
        //                 }
        //             }

        //         }


        //     }
        // }
        // //    В качестве параметра angle передавайте угол, который должен
        //    быть разным для каждого луча. Используйте такие углы:
        //    params_.rotation + 60 * 0
        //    params_.rotation + 60 * 1
        //    params_.rotation + 60 * 2
        //    ...
        //    params_.rotation + 60 * 5
        //    Вызывайте DrawRotatedVector в цикле, делающем шесть итераций.
    }
    SnowFlake GetNextLevelFlake(Point2D new_center) const {
        return SnowFlakeParams{
            .center = new_center,
            //.color = params_.color,
            .size = params_.size * params_.scale_factor,
            .line_width = params_.line_width,
            .rotation = params_.rotation,
            .depth = params_.depth - 1,
            .scale_factor = params_.scale_factor
        };
    }

    QString GetDescription() const {
        return QString("Размер %1\nТолщина линии %2\nПоворот %3\nМножитель %4")
            .arg(params_.size)
            .arg(params_.line_width)
            .arg(params_.rotation)
            .arg(params_.scale_factor);

    }

private:
    static Point2D DrawRotatedVector(prac::QPainter& painter, Point2D center, double angle, double length) {
        Vector2D lay = RotateVector(Vector2D{length, 0}, angle);
        Point2D end = Add(center, lay);

        // Нарисуйте линию от точки center до точки end.
        // Используйте метод drawLine класса painter.

        painter.drawLine(QPointF(center.x, center.y),QPointF(end.x, end.y));
        return end;
    }

private:
    SnowFlakeParams params_;
};

class WinterWindow : public QMainWindow
{
    Q_OBJECT

public:
    WinterWindow(QWidget *parent = nullptr);
    ~WinterWindow();

private slots:
    void on_btn_color_clicked();

private:
    void paintEvent(QPaintEvent *event) override;

private:
    Ui::WinterWindow *ui;
    QColor color_ = Qt::white;
    prac::QPainter painter_;
};
#endif // WINTERWINDOW_H
