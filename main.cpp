#include <QApplication>
#include "campaigntool.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    CampaignTool w;
    w.show();
    return app.exec();
}
