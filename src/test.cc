#include <QBrowseButton.h>
#include <QBrowseButton_compiler_features.h>

#include <cstddef>
#include <memory>
#include <QDebug>
#include <QApplication>

#include <functional>

// helper class that can be used to execute a lambda on scope exit
class finally {
public:
    finally(const std::function<void()>& func)
        : m_functor(func)
    {
    }
    finally(const finally&) QBrowseButton_DELETED_FUNCTION;
    finally(const finally&&) QBrowseButton_DELETED_FUNCTION;

    ~finally()
    {
        m_functor();
    }

private:
    std::function<void()> m_functor;
};

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    QBrowseButton_initResources();
    qDebug() << "QBrowseButton resources initialized successfully.";

    finally finally_QBrowseButton_resources([]() {
        qDebug() << "Cleaning up QBrowseButton resources.";
        QBrowseButton_cleanupResources();
    });

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

