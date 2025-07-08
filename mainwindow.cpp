#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFlowLayout.h"
#include "nlohmann/json.hpp"
#include <fstream>
#include <string>
#include "Templates.h"

using json = nlohmann::json;

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("ScriptApp");

    QFlowLayout *frame_layout = new QFlowLayout();
    ui->scrollAreaWidgetContents_2->setLayout(frame_layout);

    std::ifstream configfile("config.json");
    json config = json::parse(configfile);
    configfile.close();

    if (config.size()>0){
        for (auto &[key, value] : config.items()){
            frame_layout->addWidget(new ScriptFrame(key.c_str(), value.get<std::string>()));
        }
    }
    frame_layout->addWidget(new addScriptFrame(config, frame_layout));
}

Widget::~Widget()
{
    delete ui;
}