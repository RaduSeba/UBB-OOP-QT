#include "UI.h"
#include "ContractRepo.h"
#include "Service.h"
#include <QWidget>
#include <QApplication>

int main(int argc, char *argv[])
{
    testeRepo();
    testeService();
    QApplication a(argc, argv);

    FileRepo* rp = new FileRepo{ "data.txt" };
    Validator valid;
    ContractService srv{ rp,valid };

    GUI g{ srv };
    g.show();

    return a.exec();
}
