/** \file
 *
 * \brief Implementation of \a QBrowseButton
 *
 * This file provides the implementation of the \a QBrowseButton class.
 *
 * \author Peter 'png' Hille <peter@das-system-networks.de>
 *
 * \version 1.0
 */
#include <QHBoxLayout>
#include <QDebug>
#include <QMessageBox>

#include "nullptr.h"
#include "QBrowseButton.h"

/** \brief Create new QBrowseButton instance
 *
 * Initializes a new QBrowseButton widget that can be used to browse for a
 * file.
 *
 * \param parent Parent QWidget that owns the newly created QBrowseButton
 */
QBrowseButton::QBrowseButton(QWidget* parent)
    : QFrame(parent)
    , m_mode(QFileDialog::AnyFile)
    , m_caption(tr("Browse for file"))
    , m_selectedItem("")
    , m_completer(nullptr)
    , m_fileSystemModel(nullptr)
    , m_needsToExist(false)
{
    setupUi();
}

/** \brief Create new QBrowseButton for directories
 *
 * Initializes a QBrowseButton widget that can be used to browse for a
 * directory.
 *
 * \param dir Directory where the browser shall start
 * \param parent Parent QWidget that owns the newly created QBrowseButton
 */
QBrowseButton::QBrowseButton(QDir dir, QWidget* parent)
    : QFrame(parent)
    , m_mode(QFileDialog::DirectoryOnly)
    , m_caption(tr("Browse for directory"))
    , m_selectedItem(dir.absolutePath())
{
    setupUi();
    setSelectedItem(m_selectedItem);
}

/** \brief Initialize sub-widgets
 *
 * Initializes the sub-widgets that belong to the QBrowseButton instance.
 *
 * \internal This helper method is called from the class constructors to reduce code
 * redundancy for initializing all the child widgets of our button.
 */
void QBrowseButton::setupUi()
{
    QHBoxLayout* hbox = nullptr;
    try {
        hbox = new QHBoxLayout(this);
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to allocate new QVBoxLayout in" << Q_FUNC_INFO << ":" << ex.what();
        throw;
    }

    try {
        ui_leSelectedItem = new QLineEdit(m_selectedItem, this);
        ui_leSelectedItem->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        connect(ui_leSelectedItem, SIGNAL(textChanged(QString)), this, SLOT(leSelectedItem_textChanged(QString)));
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to allocate new QLineEdit in" << Q_FUNC_INFO << ":" << ex.what();
        throw;
    }

    try {
        m_completer = new QCompleter(this);
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to allocate new QCompleter in" << Q_FUNC_INFO << ":" << ex.what();
        QString message = tr("Caught exception when trying to allocate new QCompleter in %1: %2").arg(Q_FUNC_INFO, ex.what());
        QMessageBox::critical(this, tr("Out of memory"), message, QMessageBox::Ok);
        throw;
    }

    try {
        m_fileSystemModel = new QFileSystemModel(m_completer);
        m_fileSystemModel->setRootPath(QDir::rootPath());
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to allocate new QFileSystemModel in" << Q_FUNC_INFO << ":" << ex.what();
        QString message = tr("Caught exception when trying to allocate new "
                             "QFileSystemModel in %1: %2").arg(Q_FUNC_INFO, ex.what());
        QMessageBox::critical(this, tr("Out of memory"), message, QMessageBox::Ok);
        throw;
    }

    m_completer->setModel(m_fileSystemModel);
    ui_leSelectedItem->setCompleter(m_completer);

    hbox->addWidget(ui_leSelectedItem);

    try {
        ui_btnBrowse = new QPushButton(tr("..."), this);

        if (m_mode == QFileDialog::AnyFile)
            ui_btnBrowse->setIcon(QIcon::fromTheme("document-open"));
        else
            ui_btnBrowse->setIcon(QIcon::fromTheme("folder-open"));

        ui_btnBrowse->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

        connect(ui_btnBrowse, SIGNAL(clicked()), this, SLOT(btnBrowse_clicked()));

        hbox->addWidget(ui_btnBrowse);
    }

    catch (std::bad_alloc& ex) {
        qCritical() << "Caught exception when trying to allocate new QPushButton in" << Q_FUNC_INFO << ":" << ex.what();
        throw;
    }

    QFrame::setFrameStyle(QFrame::StyledPanel | QFrame::Raised);
    QFrame::setLineWidth(1);
    QFrame::setLayout(hbox);
}

/** \brief Set open mode
 *
 * This can be used to specify wether the dialog that gets opened when the user clicks the 'browse'
 * button shall be a file or directory selection dialog by using either \a QFileDialog::AnyFile or
 * \a QFileDialog::DirectoryOnly as value for the \a mode parameter.
 *
 * \note Other values for \a mode are ignored and generate a \a qWarning message!
 *
 * \param mode New selection mode for this button
 */
void QBrowseButton::setMode(QFileDialog::FileMode mode)
{
    if (!(mode == QFileDialog::AnyFile || QFileDialog::DirectoryOnly)) {
        qWarning() << "Unsupported open mode" << mode << "in" << Q_FUNC_INFO;
        return;
    }

    m_mode = mode;
}

/** \brief Set selection dialog caption
 *
 * Sets the caption for the selection dialog that is shown when the user clicks the 'browse' button.
 *
 * \param title New selection dialog caption
 */
void QBrowseButton::setCaption(QString title)
{
    m_caption = title;
}

/** \brief Set selected item
 *
 * Sets the 'selected item' box of this button to a new value.
 *
 * \param path New path that shall be shown in the 'selected item' box
 */
void QBrowseButton::setSelectedItem(QString path)
{
    m_selectedItem = path;
    ui_leSelectedItem->setText(path);
}

/** \brief Set icon for 'browse' button
 *
 * Sets the icon for the 'browse' button to a new QIcon.
 *
 * \param icon New icon for 'browse' button
 */
void QBrowseButton::setIcon(QIcon icon)
{
    ui_btnBrowse->setIcon(icon);
}

/** \brief Set 'browse' button caption
 *
 * Sets the caption of the 'browse' button to a new value.
 *
 * \param text New caption for 'browse' button
 */
void QBrowseButton::setButtonText(QString text)
{
    ui_btnBrowse->setText(text);
}

/** \brief Slot for \a clicked signal of 'browse' button
 *
 * \internal This slot is connected to the \a clicked() signal of \a ui_btnBrowse and shows
 * a file or directory selection dialog depending on the settings that have been
 * specified for this \a QBrowseButton instance.
 */
void QBrowseButton::btnBrowse_clicked()
{
    QString selection;
    switch (m_mode) {
    case QFileDialog::DirectoryOnly:
        m_fileSystemModel->setFilter(QDir::Dirs);
        selection = QFileDialog::getExistingDirectory(this, m_caption, m_selectedItem);
        break;

    case QFileDialog::AnyFile:
    default:
        m_fileSystemModel->setFilter(QDir::Files);
        selection = QFileDialog::getOpenFileName(this, m_caption, m_selectedItem, m_nameFilters.join(";;"));
        break;
    }

    if (selection.isNull())
        return;

    m_selectedItem = selection;
    ui_leSelectedItem->setText(selection);
}

void QBrowseButton::setNeedsToExist(bool needsToExist)
{
    m_needsToExist = needsToExist;
}

void QBrowseButton::leSelectedItem_textChanged(QString text)
{
    QFileInfo fileInfo(text);

    if (m_needsToExist && !fileInfo.exists())
        return;

    switch (m_mode) {
    case QFileDialog::DirectoryOnly:
        if (!fileInfo.isDir())
            return;
        break;

    default:
    case QFileDialog::AnyFile:
        if (!fileInfo.isFile())
            return;

        break;
    }

    m_selectedItem = text;
    emit newSelection(text);
}

void QBrowseButton::setNameFilters(QStringList filters)
{
    m_nameFilters = filters;
    m_fileSystemModel->setNameFilters(filters);
}
