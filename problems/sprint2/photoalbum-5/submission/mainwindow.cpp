#include "mainwindow.h"
#include "ui_mainwindow.h"

// Функция подгоняет изображение под нужный размер окна.
QPixmap ResizeImgToFit(const QPixmap &src, int window_width, int window_height) {
    int img_w = src.width();
    int img_h = src.height();

    double w_ratio = double(img_w) / window_width;
    double h_ratio = double(img_h) / window_height;

    if ( w_ratio < h_ratio ) {
        return src.scaledToWidth(window_width);
    } else {
        return src.scaledToHeight(window_height);
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Прячем основное меню.
    ui->menuBar->hide();
    // Разрешаем вызов контекстного меню на всём окне.
    this->setContextMenuPolicy(Qt::CustomContextMenu);
    // Соединяем сигнал вызова меню со слотом,
    // который напишем далее.
    connect(this, &MainWindow::customContextMenuRequested,
            this, &MainWindow::slotCustomMenuRequested);

    connect(ui -> action_up_windows, &QAction::triggered, this, &MainWindow::slotOnTop);
    void slotSetResourceFolder(bool);
    connect(ui -> action_use_resources, &QAction::triggered, this, &MainWindow::slotSetResourceFolder);
    connect(ui -> action_choose_dir, &QAction::triggered, this, &MainWindow::slotSetCustomFolder);
    connect(ui -> act_close, &QAction::triggered, this, &MainWindow::slotClose);
//    connect(&swith_timer_, &QTimer::timeout, this, &MainWindow::OnTimerTimeout);
    connect(&swith_timer_, &prac::QTimer::timeout, this, &MainWindow::OnTimerTimeout);
    connect(ui -> act_delay_off, &QAction::triggered, this, &MainWindow::slotDelayOff);
    connect(ui -> act_delay_1, &QAction::triggered, this, &MainWindow::slotDelay1);
    connect(ui -> act_delay_5, &QAction::triggered, this, &MainWindow::slotDelay5);
    connect(ui -> act_delay_10, &QAction::triggered, this, &MainWindow::slotDelay10);

    this->setWindowFlags(windowFlags().setFlag(Qt::WindowStaysOnTopHint, true));
    //   void slotSetDelay(void);

    ui ->btn_left ->setEnabled(true);
    ui ->btn_right ->setEnabled(true);


//    UpdateEnabled();
    SetFolder(default_img_folder_);

    UpdateImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::FitImage()
{
    //    Q_ASSERT(!active_pixmap.isNull());



    int win_w, win_h;
    win_w = this->width();
    win_h = this->height();
    QPixmap img_ = ResizeImgToFit(active_pixmap,win_w, win_h);

    if (img_.isNull()){
//        UpdateEnabled();
        return;
    }

    lbl_new_.setPixmap(img_);

    int img_w, img_h;
    img_w = img_.width();
    img_h = img_.height();
    // win_w, win_h — размеры окна.
    // img_w, img_h — размеры изображения.
    int lbl_x = (win_w - img_w) / 2; // Координата x.
    int lbl_y = (win_h - img_h) / 2; // Координата y.

    lbl_new_.setGeometry(lbl_x,lbl_y,img_w,img_h);

}

void MainWindow::SetFolder(const QString &new_folder){
    cur_file_index_ = 0;
    current_folder_ = new_folder;
    QPixmap img = GetImageByPath(new_folder);

    if (img.isNull()){
        SetPixmap(QString());
        // ui -> btn_left -> setEnabled(false);
        // ui -> btn_right -> setEnabled(false);
        return;
    }

//    UpdateEnabled();
    current_folder_ = new_folder;
    UpdateImage();
}

void MainWindow::UpdateImage(){
    SetPixmap(GetCurrentFile());
//    UpdateEnabled();
    FitImage();
}

QString MainWindow::GetCurrentFile(){

    QStringList list_files = current_folder_.entryList();
    // Сохраним количество файлов.
    int total = int(list_files.size());
    if (total == 0)
        return QString();

    int file_index = std::min(cur_file_index_, total - 1);
    file_index = std::max(0, file_index);
    QString path = current_folder_.filePath(list_files[file_index]);
    // Используем file_index, а не cur_file_index_.
    return path;
}

// QString MainWindow::GetCurrentFile(){
//     QDir dir(current_folder_);
//     QStringList list_files = dir.entryList(QDir::Files);
//     // Сохраним количество файлов.
//     int total = int(list_files.size());
//     if (total==0){
//         return QString();
//     }

//     int file_index = std::min(cur_file_index_, total - 1);
//     file_index = std::max(0, file_index);

//     // Используем file_index, а не cur_file_index_.
//     return dir.filePath(list_files[file_index]);
// }


void MainWindow::resizeEvent(QResizeEvent*)
{
    FitImage();
}

void MainWindow::on_btn_left_clicked() // Кнопка влево
{
    if(delay_time_ !=0)
        slotDelayOff();
    else{
        CheckIndex(false);

        UpdateImage();
    }
}



QString MainWindow::SetCustomFolder()
{
    return prac::QFileDialog::getExistingDirectory(this, QString("Открыть папку"), QDir::currentPath(),
                                                   (prac::QFileDialog::ShowDirsOnly | prac::QFileDialog::DontResolveSymlinks) );
}


void MainWindow::on_btn_right_clicked() // кнопка вправо
{
    if(delay_time_ !=0)
        slotDelayOff();
    else{
        CheckIndex(true);

        UpdateImage();
    }
}

// void MainWindow::UpdateEnabled(){

//     // Количество изображений в папке.
//     int max_images = QDir(current_folder_).entryList().size();

//     // Устанавливаем активность кнопки «влево».

//     ui->btn_left->setEnabled(cur_file_index_ > 0);

//     // Устанавливаем активность кнопки «вправо».
//     ui->btn_right->setEnabled(cur_file_index_ < max_images - 1);

// }

void MainWindow::slotOnTop(bool)
{   on_top_flag_ = !on_top_flag_;
    setWindowFlags(windowFlags().setFlag(Qt::WindowStaysOnTopHint, on_top_flag_));
    this -> show();
}

void MainWindow::slotSetResourceFolder(bool)
{
    SetFolder(default_img_folder_);
    UpdateImage();
//    UpdateEnabled();
}

void MainWindow::slotSetCustomFolder(bool)
{
    QString dir = SetCustomFolder();

    if (dir.isEmpty())
        return;
    current_folder_ = dir;
    UpdateImage();
//    UpdateEnabled();
}

void MainWindow::slotClose()
{
    MainWindow::close();
}

void MainWindow::slotSetDelay()
{
    ui -> act_delay_off ->setChecked(period == 0);
    ui -> act_delay_1 ->setChecked(period == 1000);
    ui -> act_delay_5 ->setChecked(period == 5000);
    ui -> act_delay_10 ->setChecked(period == 10000);
}

QPixmap MainWindow::GetImageByPath(QString path) const {
    QFileInfo file_info(path);
    if (!file_info.isFile()) {
        return {};
    }
    return QPixmap(path);
}

std::pair<QPixmap, int> MainWindow::FindNextImage(int start_index, int direction) const {
    QDir dir(current_folder_);
    auto file_list = dir.entryList();

    int count = file_list.size();
    int cur_image = start_index;

    for(int steps = 0; steps < count; ++steps, cur_image += direction) {
        cur_image = ((cur_image % count) + count) % count;

        auto pixmap = GetImageByPath(dir.filePath(file_list[cur_image]));
        if (!pixmap.isNull()) {
            return {pixmap, cur_image};
        }
    }
    return {{}, -1};
}

void MainWindow::OnTimerTimeout()
{
    CheckIndex(true);
//    UpdateEnabled();
    UpdateImage();
}

void MainWindow::slotDelay1()
{
    ui -> act_delay_off -> setChecked(false);
    ui -> act_delay_10 -> setChecked(false);
    ui -> act_delay_5 -> setChecked(false);

    delay_time_ = 1000;
    swith_timer_.start(delay_time_);
}

void MainWindow::slotDelay5()
{
    ui -> act_delay_1 -> setChecked(false);
    ui -> act_delay_10 -> setChecked(false);
    ui -> act_delay_off -> setChecked(false);

    delay_time_ = 5000;
    swith_timer_.start(delay_time_);
}

void MainWindow::slotDelay10()
{
    ui -> act_delay_1 -> setChecked(false);
    ui -> act_delay_off -> setChecked(false);
    ui -> act_delay_5 -> setChecked(false);

    delay_time_ = 10000;
    swith_timer_.start(delay_time_);
}

void MainWindow::slotDelayOff()
{
    delay_time_ = 0;
    swith_timer_.stop();
    ui -> act_delay_1 -> setChecked(false);
    ui -> act_delay_10 -> setChecked(false);
    ui -> act_delay_5 -> setChecked(false);
    ui -> act_delay_off ->setChecked(true);
}

void MainWindow::CheckIndex (bool direction) {
    if (direction){
        if(cur_file_index_ < (current_folder_.entryList().size()-1))
            ++cur_file_index_;
        else
            cur_file_index_ = 0;
    }
    else
    {        if(cur_file_index_ < 2)
            --cur_file_index_;
        else
            cur_file_index_ = (current_folder_.entryList().size()-1);

}
}
