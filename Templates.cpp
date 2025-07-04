#include <QtWidgets>
#include "Templates.h"
#include <iostream>

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

    qDebug() << script_command;
}

void ScriptFrame::ButtonClick(){
    QProcess process;
    process.startDetached(script_command.c_str());
}

void ScriptFrame::ButtonClick2(){
    QProcess process;
    QStringList arguments;
    arguments << "/c" << "start" << "cmd.exe" << "/k" << script_command.c_str();
    qDebug() << arguments;
    process.startDetached("cmd.exe", arguments);
}