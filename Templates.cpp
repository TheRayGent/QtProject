#include <QtWidgets>
#include "Templates.h"
#include <fstream>

using json = nlohmann::json;

ScriptFrame::ScriptFrame(const QString &title, std::string script_text): QFrame(), script_command(script_text) {
    setFixedSize(201,121);
    setFrameShape(QFrame::StyledPanel);

    activate_script_button = new QPushButton(this);
    activate_script_button2 = new QPushButton(this);
    script_name = new QLabel(this);
    
    QFont font("Gotham Pro", 15);
    script_name->setFont(font);
    script_name->setText(title);
    script_name->move(width()/2-script_name->width()/2, 10);
    
    activate_script_button->setFixedSize(53,51);
    activate_script_button->move(35,50);
    activate_script_button->setIconSize(QSize(26,26));
    activate_script_button->setIcon(QIcon::fromTheme("media-playback-start"));
    activate_script_button->setToolTip("Выполнить без консоли");

    activate_script_button2->setFixedSize(53,51);
    activate_script_button2->move(120,50);
    activate_script_button2->setIconSize(QSize(26,26));
    activate_script_button2->setIcon(QIcon::fromTheme("window-new"));
    activate_script_button2->setToolTip("Выполнить с консолью");

    connect(activate_script_button, &QPushButton::clicked, this, &ScriptFrame::ButtonClick);
    connect(activate_script_button2, &QPushButton::clicked, this, &ScriptFrame::ButtonClick2);
}

ScriptFrame::~ScriptFrame(){
    delete activate_script_button2;
    delete activate_script_button;
    delete script_name;
}

void ScriptFrame::ButtonClick(){
    QProcess process;
    process.startDetached(script_command.c_str());
}

void ScriptFrame::ButtonClick2(){
    QProcess process;
    QStringList arguments;
    arguments << "/c" << "start" << "cmd.exe" << "/k" << script_command.c_str();
    process.startDetached("cmd.exe", arguments);
}

addScriptFrame::addScriptFrame(json configdata, QFlowLayout * parent_layout_point): QFrame(), config(configdata), parent_layout(parent_layout_point){
    setFixedSize(201,121);
    setFrameShape(QFrame::StyledPanel);

    add_script_button = new QPushButton(this);
    add_script_line = new QLineEdit(this);
    add_script_name = new QLineEdit(this);

    QFont font("Cascadia Mono", 10);
    add_script_name->setFont(font);
    add_script_name->setFixedSize(171,26);
    add_script_name->move(14,8);
    add_script_name->setPlaceholderText("Введите название");

    QFont font1("Cascadia Mono", 10);
    add_script_line->setFont(font1);
    add_script_line->setFixedSize(171,26);
    add_script_line->move(14,39);
    add_script_line->setPlaceholderText("Введите скрипт");

    add_script_button->setFixedSize(40,40);
    add_script_button->move(79,70);
    add_script_button->setIconSize(QSize(26,26));
    add_script_button->setIcon(QIcon::fromTheme("list-add"));
    add_script_button->setToolTip("Добавить скрипт/комманду");

    connect(add_script_button, &QPushButton::clicked, this, &addScriptFrame::ButtonClick);
}

void addScriptFrame::ButtonClick(){
    config[add_script_name->text().toStdString()] = add_script_line->text().toStdString();
    std::ofstream configfile("config.json");
    configfile << config.dump(2);
    configfile.close();
    parent_layout->removeWidget(this);
    parent_layout->addWidget(new ScriptFrame(add_script_name->text(), add_script_line->text().toStdString()));
    parent_layout->addWidget(this);
}