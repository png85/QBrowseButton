/** \file
 *
 * \brief Declaration of \a QBrowseButtonDesignerFactory
 *
 * This file provides the prototypes of the Qt Designer plugin for
 * \a QBrowseButton.
 *
 * \author Peter 'png' Hille <peter@das-system-networks.de>
 *
 * \version 1.0
 */
#ifndef QBROWSEBUTTONDESIGNERFACTORY_H
#define QBROWSEBUTTONDESIGNERFACTORY_H

#include <QObject>
#include <QtDeclarative/QDeclarativeItem>
#include <QtDesigner/QDesignerCustomWidgetInterface>

/** \brief Qt Designer plugin for \a QBrowseButton
 *
 * This class provides a Qt Designer plugin which enables the \a QBrowseButton
 * class to be used for UI design.
 *
 * \author Peter 'png' Hille <peter@das-system-networks.de>
 *
 * \version 1.0 Initial implementation
 */
class QBrowseButtonDesignerFactory : public QObject,
                                     public QDesignerCustomWidgetInterface {
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit QBrowseButtonDesignerFactory(QDeclarativeItem* parent = 0);

    virtual QWidget* createWidget(QWidget* parent);
    virtual QString group() const;
    virtual QIcon icon() const;
    virtual QString includeFile() const;
    virtual bool isContainer() const;
    virtual QString name() const;
    virtual QString toolTip() const;
    virtual QString whatsThis() const;

signals:

public slots:
};

#endif // QBROWSEBUTTONDESIGNERFACTORY_H
