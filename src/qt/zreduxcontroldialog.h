// Copyright (c) 2017-2018 The Redux developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef ZREDUXCONTROLDIALOG_H
#define ZREDUXCONTROLDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "zredux/zerocoin.h"
#include "privacydialog.h"

class CZerocoinMint;
class WalletModel;

namespace Ui {
class ZReduxControlDialog;
}

class CZReduxControlWidgetItem : public QTreeWidgetItem
{
public:
    explicit CZReduxControlWidgetItem(QTreeWidget *parent, int type = Type) : QTreeWidgetItem(parent, type) {}
    explicit CZReduxControlWidgetItem(int type = Type) : QTreeWidgetItem(type) {}
    explicit CZReduxControlWidgetItem(QTreeWidgetItem *parent, int type = Type) : QTreeWidgetItem(parent, type) {}

    bool operator<(const QTreeWidgetItem &other) const;
};

class ZReduxControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ZReduxControlDialog(QWidget *parent);
    ~ZReduxControlDialog();

    void setModel(WalletModel* model);

    static std::set<std::string> setSelectedMints;
    static std::set<CMintMeta> setMints;
    static std::vector<CMintMeta> GetSelectedMints();

private:
    Ui::ZReduxControlDialog *ui;
    WalletModel* model;
    PrivacyDialog* privacyDialog;

    void updateList();
    void updateLabels();

    enum {
        COLUMN_CHECKBOX,
        COLUMN_DENOMINATION,
        COLUMN_PUBCOIN,
        COLUMN_VERSION,
        COLUMN_PRECOMPUTE,
        COLUMN_CONFIRMATIONS,
        COLUMN_ISSPENDABLE
    };
    friend class CZReduxControlWidgetItem;

private slots:
    void updateSelection(QTreeWidgetItem* item, int column);
    void ButtonAllClicked();
};

#endif // ZREDUXCONTROLDIALOG_H
