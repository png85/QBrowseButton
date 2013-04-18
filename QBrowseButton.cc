#include <QVBoxLayout>
#include <QDebug>

#include "nullptr.h"
#include "QBrowseButton.h"


QBrowseButton::QBrowseButton(QWidget *parent) :
    QFrame(parent), m_mode(QFileDialog::AnyFile), m_caption(tr("Browse for file")),
    m_buttonText(tr("...")), m_selectedItem("")
{
    setupUi();
    setSelectedItem(QDir::currentPath());
}


QBrowseButton::QBrowseButton(QDir dir, QWidget *parent) :
    QFrame(parent), m_mode(QFileDialog::DirectoryOnly), m_caption(tr("Browse for directory")),
    m_buttonText(tr("...")), m_selectedItem(dir.absolutePath())
{
    setupUi();
    setSelectedItem(m_selectedItem);
}


void QBrowseButton::setupUi() {
    QVBoxLayout* vbox = nullptr;
    try {
        vbox = new QVBoxLayout(this);
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to allocate new QVBoxLayout in" << Q_FUNC_INFO << ":" << ex.what();
        throw;
    }

    try {
        ui_leSelectedItem = new QLineEdit(m_selectedItem, this);
        ui_leSelectedItem->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
        vbox->addWidget(ui_leSelectedItem);
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to allocate new QLineEdit in" << Q_FUNC_INFO << ":" << ex.what();
        throw;
    }

    try {
        ui_btnBrowse = new QPushButton(tr("Browse"), this);

        if (m_mode == QFileDialog::AnyFile)
            ui_btnBrowse->setIcon(QIcon::fromTheme("folder-open"));
        else
            ui_btnBrowse->setIcon(QIcon::fromTheme("folder-open"));

        ui_btnBrowse->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        connect(ui_btnBrowse, SIGNAL(clicked()), this, SLOT(btnBrowse_clicked()));

        vbox->addWidget(ui_btnBrowse);
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to allocate new QPushButton in" << Q_FUNC_INFO << ":" << ex.what();
        throw;
    }

    QFrame::setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    QFrame::setLineWidth(2);
    QFrame::setLayout(vbox);
}


void QBrowseButton::setMode(QFileDialog::FileMode mode) {
    if (!(mode == QFileDialog::AnyFile || QFileDialog::DirectoryOnly)) {
        qWarning() << "Unsupported open mode" << mode << "in" << Q_FUNC_INFO;
        return;
    }

    m_mode = mode;
}


void QBrowseButton::setCaption(QString title) {
    m_caption = title;
}


void QBrowseButton::setSelectedItem(QString path) {
    m_selectedItem = path;
    ui_leSelectedItem->setText(path);
}


void QBrowseButton::setIcon(QIcon icon) {
    ui_btnBrowse->setIcon(icon);
}


void QBrowseButton::btnBrowse_clicked() {
    QString selection;
    switch (m_mode) {
    default:
    case QFileDialog::AnyFile:
        selection = QFileDialog::getOpenFileName(this, m_caption, m_selectedItem, "*");
        break;

    case QFileDialog::DirectoryOnly:
        selection = QFileDialog::getExistingDirectory(this, m_caption, m_selectedItem);
        break;
    }

    if (selection.isNull())
        return;

    m_selectedItem = selection;

    emit newSelection(selection);
}
