#pragma once
#include "Service.h"
#include "Observer.h"
#include "LstContract.h"
#include <set>
#include <QWidget>
#include <QListWidget>
#include <QBoxLayout>
#include <QPushButton>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QTableWidget>
#include <QPainter>
#include <QSlider>
#include "MyList.h"



class ListaGUI :public QWidget, public Observer {

private:
    ListaContract& rep;
    ContractService& srv;
    QHBoxLayout* recipe_main_layout = new QHBoxLayout;
    QListWidget* recipe_lst;

    QLineEdit* lne_recipe;
    QPushButton* add_to_rec;
    QPushButton* empty_rec;
    QPushButton* random_add;
    QPushButton* export_recipe;
    QPushButton* help_button;
    void initGUI();
    void connectSignals();
    void reloadDis(vector<Disciplina> dis);
    void update() override {
        reloadDis(rep.getallContractDiscipline());
    }
public:

    ListaGUI(ListaContract& rep, ContractService& srv) : srv{srv}, rep{rep}{
        rep.addObs(this);
        initGUI();
        connectSignals();
        reloadDis(rep.getallContractDiscipline());
    }

    ~ListaGUI() {
        rep.rmObs(this);
    }

};

class PaintGUI : public QWidget, public Observer {
private:
   ListaContract& rep;
public:
    PaintGUI(ListaContract& rep) :rep{ rep } {
        rep.addObs(this);
    }

    void paintEvent(QPaintEvent*) override {
        QPainter p{ this };
        int x;
        int y;
        for (auto& it : rep.getallContractDiscipline()) {
           // p.drawRect(x, y, 10, .getDurata() * 10);
            x = rand() % 400 + 1;
            y = rand() % 400 + 1;
            //qDebug() << x << " " << y;
            QRectF target(x, y, 100, 94);
            QRectF source(0, 0, 1000, 1000);
            QImage image("vilut.jpg");
            //QImage image2("seba.jpg");

            p.drawImage(target, image, source);
       
            /*p.drawLine(0, 0, width(), height());
            p.drawImage(x, 0, QImage("sky.jpg"));
            p.setPen(Qt::blue);
            p.setFont(QFont("Arial", 30));
            p.drawText(rect(), Qt::AlignTop | Qt::AlignHCenter, "Qt QPainter");
            p.fillRect(0, 100, 100, 100, Qt::BrushStyle::Dense1Pattern);*/
            x += 40;
        }
    }

    void update() override {
        repaint();
    }

    ~PaintGUI() {
        rep.rmObs(this);
    }
};







class GUI : public QWidget {
private:

    vector<Disciplina> act_list;



    ListaContract rep;
    ContractService srv;
    QListWidget* lst=new QListWidget;


    QListView* lst_view = new QListView;
    MyListModel* model;

    vector<ListaGUI* > rcp;
    vector<PaintGUI*> pg;


    //QTableWidget* tabel;
    QHBoxLayout* lyMain = new QHBoxLayout;
    QPushButton* btnSortName;
    QPushButton* btnSortProd;
    QPushButton* btnSortOre;
    QPushButton* btnFilterOre;
    QPushButton* btnFilterCadru;
    QPushButton* btn_lst_mst;
    QPushButton* btn_lst_rdonly;
    QPushButton* btn_reset;
    QPushButton* btn_add;
    QPushButton* btn_mod;
    QPushButton* btn_del;
    QPushButton* btn_undo;
    QWidget* opt_but;
    vector<QPushButton*> disciplina_but;
    QVBoxLayout* lay_opt;
    QLineEdit* txtDenumire;
    QLineEdit* txtOre;
    QLineEdit* txtCadru;
    QLineEdit* txtTip;
    QLineEdit* txtFilterOre;
    QLineEdit* txtFilterCadru;
    QMessageBox filterbox;
    QWidget* fWidget;
    QListWidget* lst_contract;
    QSlider* plm;
    int lb_index;
    void init_GUI();
    void connectSignalsSlots();
    void clearLayout(QLayout* layout);
    void reloadList(vector<Disciplina>& dis);

    void addMed();
    void delMed();
    void uptMed();
    void undoGUI();
    void updateBut(vector<Disciplina>& all);

    void reset_form();
public:
    GUI(ContractService& srv) : srv{ srv } {
        init_GUI();
        model = new MyListModel(srv.getAllDiscipline());
        lst_view->setModel(model);
        connectSignalsSlots();
        reloadList(srv.getAllDiscipline());
        act_list = srv.getAllDiscipline();
        updateBut(srv.getAllDiscipline());
        rcp.push_back(new ListaGUI{ rep,srv });
        rcp[0]->show();
        pg.push_back(new PaintGUI{ rep });
        pg[0]->show();
        
    }
};