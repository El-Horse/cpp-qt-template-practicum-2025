#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint);

    for (const auto& action : actions_) {
        ui->cb_action->addItem(action.name);
    }
    ui -> cb_action -> addItem("Открыть URL");
    ui -> cb_action -> addItem("Открыть папку");
}

Setting::~Setting() {
    delete ui;
}

void Setting::on_pb_save_clicked() {
    QString user_input;
    // auto open_ = [=, this] (const QString o_url) -> void{
    //     QString str_url = "Открыть URL " + o_url;
    //     emit signalSetAction(current_button_idx_, str_url, OpenCustomUrl);
    // };

    auto index = ui->cb_action->currentIndex();
    if (index < 0 || static_cast<size_t>(index) >= (actions_.size()+1)) {
        return;
    }
    if (index == actions_.size()){
       user_input = prac::QInputDialog::getText(this, "Введите URL", "URL:");
        OpenCustomUrl(prac::QInputDialog::getText(this, "Введите URL", "URL:"));
          // open_(user_input);
    }
    else if (index == actions_.size()+1){
        OpenCustomDirectory(prac::QInputDialog::getText(this, "Введите URL", "URL:"));
    }
    else{
        emit signalSetAction(current_button_idx_, actions_[index].name, actions_[index].action);

    }
        ui->cb_action->setCurrentIndex(0);
    this->close();
}
