// Copyright (c) 2011-2013 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_QT_ASKPASSREDUXASEDIALOG_H
#define BITCOIN_QT_ASKPASSREDUXASEDIALOG_H

#include <QDialog>

class WalletModel;

namespace Ui
{
class AskPassreduxaseDialog;
}

/** Multifunctional dialog to ask for passreduxases. Used for encryption, unlocking, and changing the passreduxase.
 */
class AskPassreduxaseDialog : public QDialog
{
    Q_OBJECT

public:
    enum Mode {
        Encrypt,         /**< Ask passreduxase twice and encrypt */
        UnlockAnonymize, /**< Ask passreduxase and unlock only for anonymization */
        Unlock,          /**< Ask passreduxase and unlock */
        ChangePass,      /**< Ask old passreduxase + new passreduxase twice */
        Decrypt          /**< Ask passreduxase and decrypt wallet */
    };

    explicit AskPassreduxaseDialog(Mode mode, QWidget* parent, WalletModel* model);
    ~AskPassreduxaseDialog();

    void accept();

private:
    Ui::AskPassreduxaseDialog* ui;
    Mode mode;
    WalletModel* model;
    bool fCapsLock;

private slots:
    void textChanged();

protected:
    bool event(QEvent* event);
    bool eventFilter(QObject* object, QEvent* event);
};

#endif // BITCOIN_QT_ASKPASSREDUXASEDIALOG_H
