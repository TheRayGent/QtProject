#ifndef TEMPLATES_H
#define TEMPLATES_H

#include <QFrame>
#include <QPushButton>
#include <QLabel>
class ScriptFrame : public QFrame
{
public:
    ScriptFrame(const QString &title, std::string script_text);
private:
    QPushButton * activate_script_button;
    QPushButton * activate_script_button2;
    QLabel * script_name;
    std::string script_command;
private slots:
    void ButtonClick();
    void ButtonClick2();
};

#endif // TEMPLATES_H