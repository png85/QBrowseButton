#ifndef QBROWSEBUTTON_H
#define QBROWSEBUTTON_H

#include <QObject>
#include <QDir>
#include <QFrame>
#include <QLineEdit>
#include <QPushButton>

#include <QFileDialog>

class QBrowseButton : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(QFileDialog::FileMode mode READ mode WRITE setMode)
    Q_PROPERTY(QString caption READ caption WRITE setCaption)
    Q_PROPERTY(QString buttonText READ buttonText WRITE setButtonText)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(QString selectedItem READ selectedItem WRITE setSelectedItem)

public:
    QBrowseButton(QWidget* parent=0);
    QBrowseButton(QDir dir, QWidget* parent=0);

    QFileDialog::FileMode mode() const { return m_mode; }
    QString caption() const { return m_caption; }
    QString buttonText() const { return m_buttonText; }
    QString selectedItem() const { return m_selectedItem; }
    QIcon icon() const { return ui_btnBrowse->icon(); }

public slots:
    void setMode(QFileDialog::FileMode mode);
    void setCaption(QString caption);
    void setButtonText(QString text);
    void setSelectedItem(QString path);
    void setIcon(QIcon icon);

signals:
    void newSelection(QString selectedItem);

private slots:
    void btnBrowse_clicked();

private:
    QFileDialog::FileMode m_mode;
    QString m_caption;
    QString m_buttonText;
    QString m_selectedItem;

    QLineEdit* ui_leSelectedItem;
    QPushButton* ui_btnBrowse;
    void setupUi();
};

#endif // QBROWSEBUTTON_H
