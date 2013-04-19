#ifndef QBROWSEBUTTONDESIGNERFACTORY_H
#define QBROWSEBUTTONDESIGNERFACTORY_H

#include <QObject>
#include <QtDeclarative/QDeclarativeItem>
#include <QtDesigner/QDesignerCustomWidgetInterface>

class QBrowseButtonDesignerFactory : public QObject,
        public QDesignerCustomWidgetInterface
{
    Q_OBJECT
    Q_INTERFACES(QDesignerCustomWidgetInterface)
public:
    explicit QBrowseButtonDesignerFactory(QDeclarativeItem *parent = 0);
    
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
