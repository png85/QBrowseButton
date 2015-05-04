#include <QBrowseButton.h>
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    QBrowseButton_initResources();

    QBrowseButton* b = new QBrowseButton();
    b->show();

    return a.exec();
}
