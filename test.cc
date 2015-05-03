#include <QApplication>

#include "QBrowseButton.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    QBrowseButton* b = new QBrowseButton();
    b->show();

    return a.exec();
}
