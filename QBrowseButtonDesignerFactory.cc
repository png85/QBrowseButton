#include <QDebug>
#include <QMessageBox>
#include <QtPlugin>

#include "nullptr.h"
#include "QBrowseButton.h"
#include "QBrowseButtonDesignerFactory.h"

QBrowseButtonDesignerFactory::QBrowseButtonDesignerFactory(QDeclarativeItem *parent) :
    QObject(parent)
{
}


QWidget* QBrowseButtonDesignerFactory::createWidget(QWidget *parent) {
    QBrowseButton* widget = nullptr;
    try {
        widget = new QBrowseButton(parent);
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to allocate new QBrowseButton in" << Q_FUNC_INFO << ":" << ex.what();
        QString message = tr("Caught exception when trying to create new QBrowseButton"
                             "instance in %0: %1").arg(Q_FUNC_INFO, ex.what());
        QMessageBox::critical(parent, tr("Out of memory"), message, QMessageBox::Ok);
        throw;
    }

    return reinterpret_cast<QWidget*>(widget);
}


QString QBrowseButtonDesignerFactory::group() const {
    return "#das-system Networks";
}


QIcon QBrowseButtonDesignerFactory::icon() const {
    return QIcon::fromTheme("folder-open");
}


QString QBrowseButtonDesignerFactory::includeFile() const {
    return "QBrowseButton.h";
}


QString QBrowseButtonDesignerFactory::toolTip() const {
    return tr("File/Directory Browse Button");
}


QString QBrowseButtonDesignerFactory::whatsThis() const {
    return tr("Button to browse for directories or files.");
}


bool QBrowseButtonDesignerFactory::isContainer() const {
    return false;
}


QString QBrowseButtonDesignerFactory::name() const {
    return "QBrowseButton";
}


Q_EXPORT_PLUGIN2(QBrowseButtonDesignerPlugin, QBrowseButtonDesignerFactory)
