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
    //frame_layout->takeAt(1)->widget()->~QWidget();
}

Widget::~Widget()
{
    delete ui;
}

// {
//     QLayout *layout = (ui->scrollAreaWidgetContents->layout());
//     qDebug() << layout;
//     int index1 = 0;
//     int index2 = 2;
//     // 1. Получаем элементы
//     QLayoutItem *item1 = layout->itemAt(index1);
//     QLayoutItem *item2 = layout->itemAt(index2);

//     if (!item1 || !item2)
//         return;

//     // 2. Сохраняем элементы (в данном случае, только виджеты)
//     QWidget *widget1 = item1->widget();
//     QWidget *widget2 = item2->widget();

//     // 3. Сохраняем все элементы во временный вектор и удаляем их из layout
//     std::vector<QLayoutItem *> items;
//     while (layout->count() > 0)
//     {
//         QLayoutItem *item = layout->takeAt(0);
//         items.push_back(item);
//     }

//     // 4.  Вставляем виджеты в нужном порядке

//     int realIndex1 = -1;
//     int realIndex2 = -1;
//     for (size_t i = 0; i < items.size(); ++i)
//     {
//         if (items[i]->widget() == widget1)
//             realIndex1 = i;
//         if (items[i]->widget() == widget2)
//             realIndex2 = i;
//     }

//     if (realIndex1 == -1 || realIndex2 == -1)
//         return;

//     std::swap(items[realIndex1], items[realIndex2]);

//     for (QLayoutItem *item : items)
//     {
//         layout->addItem(item);
//     }
// }