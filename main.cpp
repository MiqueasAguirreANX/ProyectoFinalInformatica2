#include <QApplication>
#include <QFont>
#include <QPushButton>

#include "menu.h"

class Menu;

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    Menu *menu = new Menu();

    menu->show();

    return app.exec();
}
