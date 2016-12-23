#include "campaigntool.h"
#include "ui_campaigntool.h"
#include "mapnode.h"
#include "dice.h"
#include "mech.h"

CampaignTool::CampaignTool(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CampaignTool)
{
    Mech *mech;

    mech = new Mech();
    mech->load("mech_TM-A_1");
    qDebug() << mech->toStringList();
    mech->~Mech();

    mech= new Mech();
    mech->create("LCT-1V");
    mech->save();
    mech->~Mech();

    mech = new Mech();
    mech->create("STG-3R");
    mech->save();
    mech->~Mech();

    mech = new Mech();
    mech->create("WSP-1A");
    mech->save();
    mech->~Mech();

    ui->setupUi(this);
    //straMapModel.initMap(new MapNode("/home/gardan/Qt4/Btech/CampaignTool/mission/finalwar/map.txt"));
    straMapModel.initMap(new MapNode("missiondata/finalwar/map.txt"));
    straMapModel.root()->save("missiondata/finalwar/map_save.txt");
    tactMapModel.initMap(straMapModel.root());
    tactMapModel.setMap(MapNode::TacticalMap, 0, 0);

    strategicView = new QTableView(parent);
    strategicView = ui->strategicView;
    strategicView->setModel(&straMapModel);
    strategicView->show();

    tacticalView = new QTableView(parent);
    tacticalView = ui->tacticalView;
    tacticalView->setModel(&tactMapModel);
    tacticalView->show();

    strategicLabel = new QLabel;
    strategicLabel = ui->strategicLabel;
    strategicLabel->setText(QString("noppatesti %1 %2 %3 %4 %5 %6 %7 %8").arg(d6.roll(4)).arg(d6.roll(4)).arg(d6.roll(4)).arg(d6.roll(4)).arg(d6.roll(4)).arg(d6.roll(4)).arg(d6.roll(4)).arg(d6.roll(4))); // "Argyle Valley, Skye"); // ToDo: from root node
    tacticalLabel = new QLabel;
    tacticalLabel = ui->tacticalLabel;
    tacticalLabel->setText("Grid A0"); // ToDo: from root node

    closeButton = new QPushButton;
    closeButton = ui->closeButton;

    connect(closeButton, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(strategicView, SIGNAL(clicked(QModelIndex)), this, SLOT(strategicNodeClicked(QModelIndex)));
}

CampaignTool::~CampaignTool()
{
    delete ui;
}

void CampaignTool::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);

    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void CampaignTool::strategicNodeClicked(const QModelIndex & index)
{
    qDebug() << "strategicNodeClicked " << index.row()<< "," << index.column();
    tactMapModel.setMap(MapNode::TacticalMap, index.row(), index.column());
    tacticalView->show();
    tacticalLabel->setText("Grid "+QString(QChar('A'+index.row()))+QString(QChar('0'+index.column()+1)));
}
