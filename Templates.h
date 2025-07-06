#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <QFrame>
#include <QPushButton>
#include <QLabel>
#include "nlohmann/json.hpp"
#include "QFlowLayout.h"
class ScriptFrame : public QFrame
{
public:
    ScriptFrame(const QString &title, std::string script_text);
    ~ScriptFrame();
private:
    QPushButton * activate_script_button;
    QPushButton * activate_script_button2;
    QLabel * script_name;
    std::string script_command;
private slots:
    void ButtonClick();
    void ButtonClick2();
};


class addScriptFrame : public QFrame
{
public:
    addScriptFrame(nlohmann::json configdata, QFlowLayout * parent_layout_point);
private:
    QPushButton * add_script_button;
    QLineEdit * add_script_line;
    QLineEdit * add_script_name;
    nlohmann::json config;
    QFlowLayout * parent_layout;
private slots:
    void ButtonClick();
};

#endif // TEMPLATES_H