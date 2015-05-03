/** \file
 *
 * \brief Declaration of \a QBrowseButton
 *
 * This file provides the declaration of the \a QBrowseButton class.
 *
 * \author Peter 'png' Hille <peter@das-system-networks.de>
 *
 * \version 1.0
 */
#ifndef QBROWSEBUTTON_H
#define QBROWSEBUTTON_H

#include <QBrowseButton_Export.h>

#include <QObject>
#include <QDir>
#include <QFrame>
#include <QLineEdit>
#include <QPushButton>

#include <QFileDialog>

#include <QAbstractItemModel>
#include <QCompleter>
#include <QFileSystemModel>

/** \brief 'Browse...' button for files or directories
 *
 * This class provides a simple button to browse for files or directories.
 *
 * \author Peter 'png' Hille <peter@das-system-networks.de>
 *
 * \version 1.0 Initial implementation
 */
class QBrowseButton_EXPORT QBrowseButton : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(QFileDialog::FileMode mode READ mode WRITE setMode)
    Q_PROPERTY(QString caption READ caption WRITE setCaption)
    Q_PROPERTY(QString buttonText READ buttonText WRITE setButtonText)
    Q_PROPERTY(QIcon icon READ icon WRITE setIcon)
    Q_PROPERTY(QString selectedItem READ selectedItem WRITE setSelectedItem)
    Q_PROPERTY(bool needsToExist READ needsToExist WRITE setNeedsToExist)
    Q_PROPERTY(QStringList nameFilters READ nameFilters WRITE setNameFilters)

public:
    QBrowseButton(QWidget* parent=0);
    QBrowseButton(QDir dir, QWidget* parent=0);

    /** \brief Get current selection mode
     *
     * Returns the current selection mode for this QBrowseButton.
     *
     * \see setMode
     * \see m_mode
     */
    QFileDialog::FileMode mode() const { return m_mode; }

    /** \brief Get dialog caption
     *
     * Returns the caption for the dialog box that is shown when the user
     * clicks the 'browse' button.
     *
     * \see setCaption
     * \see m_caption
     */
    QString caption() const { return m_caption; }

    /** \brief Get button caption
     *
     * Returns the caption for the 'browse' button.
     *
     * \see setButtonText
     * \see m_buttonText
     */
    QString buttonText() const { return ui_btnBrowse->text(); }

    /** \brief Get currently selected item
     *
     * Returns the path or file that has been selected in this QBrowseButton.
     *
     * \see setSelectedItem
     * \see m_selectedItem
     */
    QString selectedItem() const { return m_selectedItem; }


    /** \brief Get button icon
     *
     * Returns the current icon of the 'browse' button.
     *
     * \see ui_btnBrowse
     */
    QIcon icon() const { return ui_btnBrowse->icon(); }

    bool needsToExist() const { return m_needsToExist; }

    QStringList nameFilters() const { return m_nameFilters; }

public slots:
    void setMode(QFileDialog::FileMode mode);
    void setCaption(QString caption);
    void setButtonText(QString text);
    void setSelectedItem(QString path);
    void setIcon(QIcon icon);
    void setNeedsToExist(bool);
    void setNameFilters(QStringList filters);

signals:
    void newSelection(QString selectedItem);

private slots:
    void btnBrowse_clicked();
    void leSelectedItem_textChanged(QString text);

private:
    /** \brief Current selection mode
     *
     * Specifies wether the widget is used to browse for a file or directory.
     */
    QFileDialog::FileMode m_mode;

    /** \brief Dialog box caption
     *
     * Holds the caption for the dialog box that is displayed when the user clicks
     * the 'browse' button.
     */
    QString m_caption;

    /** \brief Selected file or directory
     *
     * Holds the filename or directory that has been selected in this QBrowseButton.
     */
    QString m_selectedItem;

    /** \brief Text box for selected file
     *
     * Contains the currently selected filename or directory.
     *
     * \see m_selectedItem
     */
    QLineEdit* ui_leSelectedItem;

    /** \brief 'Browse' button
     *
     * This button shows a QFileDialog with the settings that have been configured when
     * it's clicked.
     */
    QPushButton* ui_btnBrowse;

    QCompleter *m_completer;
    QFileSystemModel* m_fileSystemModel;
    bool m_needsToExist;

    QStringList m_nameFilters;

    void setupUi();
};

#endif // QBROWSEBUTTON_H
