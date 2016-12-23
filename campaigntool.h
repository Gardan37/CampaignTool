#ifndef CAMPAIGNTOOL_H
#define CAMPAIGNTOOL_H

#include <QMainWindow>
#include <QtGui>
#include "mapmodel.h"
#include "mapnode.h"
#include "ui_campaigntool.h"

namespace Ui {
    class CampaignTool;
}

class MapModel;
class MapNode;

class CampaignTool : public QMainWindow
{
    Q_OBJECT
public:
    CampaignTool(QWidget *parent = 0);
    ~CampaignTool();

protected:
    void changeEvent(QEvent *e);

public slots:
    void strategicNodeClicked(const QModelIndex & index);

private:
    //Ui::CampaignTool *ui;
    Ui::CampaignTool *ui;

    MapModel straMapModel;
    MapModel tactMapModel;
    QLabel *strategicLabel;
    QLabel *tacticalLabel;
    QTableView *strategicView;
    QTableView *tacticalView;
    QPushButton *closeButton;

    MapNode *getRootNode();
    QMap<QString, QVariant> parseNodeStr(QString nodeStr);
};

#endif // CAMPAIGNTOOL_H
