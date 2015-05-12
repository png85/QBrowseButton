#include <QBrowseButton.h>

#include <cstddef>
#include <memory>
#include <QDebug>
#include <QApplication>

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    QBrowseButton_initResources();

    try {
        std::unique_ptr<QBrowseButton> bb(new QBrowseButton());
        bb->show();
        return a.exec();
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Failed to allocate memory for QBrowseButton: " << ex.what();
        return EXIT_FAILURE;
    }

    return EXIT_FAILURE; // this should never be reached
}
