/** \file
 *
 * \brief Implementation of \a QBrowseButtonDesignerFactory
 *
 * This file provides the implementation of the Qt Designer plugin for
 * \a QBrowseButton.
 *
 * \author Peter 'png' Hille <peter@das-system-networks>
 *
 * \version 1.0
 */
#include <QDebug>
#include <QMessageBox>
#include <QtPlugin>

#include "nullptr.h"
#include "QBrowseButton.h"
#include "QBrowseButtonDesignerFactory.h"


/** \brief Default constructor
 *
 * Initializes the QBrowseButton factory for Qt Designer.
 */
QBrowseButtonDesignerFactory::QBrowseButtonDesignerFactory(QDeclarativeItem *parent) :
    QObject(parent)
{
    // ... nothing ...
}


/** \brief Create QBrowseButton instance
 *
 * Creates a new QBrowseButton widget for use in Qt Designer.
 *
 * \param parent Parent QWidget of the newly created QBrowseButton
 *
 * \return Pointer to newly created QBrowseButton instance
 */
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


/** \brief Widget group name
 *
 * \return Name of the group under which our widget shall show up in Qt Designer
 */
QString QBrowseButtonDesignerFactory::group() const {
    return "#das-system";
}


/** \brief Widget icon
 *
 * \return Icon to show in Qt Designer's widget list
 */
QIcon QBrowseButtonDesignerFactory::icon() const {
    return QIcon::fromTheme("folder-open");
}


/** \brief Header name for Qt Designer
 *
 * \return Name of C++ header to include for our widget
 */
QString QBrowseButtonDesignerFactory::includeFile() const {
    return "QBrowseButton.h";
}


/** \brief Tooltip text
 *
 * \return Tooltip text that is shown for our widget
 */
QString QBrowseButtonDesignerFactory::toolTip() const {
    return tr("File/Directory Browse Button");
}


/** \brief "What's this?" description
 *
 * \return Descriptive text for "What's This?"
 */
QString QBrowseButtonDesignerFactory::whatsThis() const {
    return tr("Button to browse for directories or files.");
}


/** \brief Is our widget a container?
 *
 * \return Boolean flag indicating wether our widget is a container (false)
 */
bool QBrowseButtonDesignerFactory::isContainer() const {
    return false;
}


/** \brief Widget name
 *
 * \return Name of our widget to show in Qt Designer
 */
QString QBrowseButtonDesignerFactory::name() const {
    return "QBrowseButton";
}


Q_EXPORT_PLUGIN2(QBrowseButtonDesignerPlugin, QBrowseButtonDesignerFactory)
