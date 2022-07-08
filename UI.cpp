#include "UI.h"

void GUI::init_GUI() {
    setLayout(lyMain);

    QWidget* w_left = new QWidget;
    QVBoxLayout* l_left = new QVBoxLayout;
    w_left->setLayout(l_left);
    // tabel = new QTableWidget(this);

    lst_view->setUniformItemSizes(true);

    l_left->addWidget(lst_view);

    QWidget* wdg = new QWidget;
    QHBoxLayout* lay = new QHBoxLayout;
    wdg->setLayout(lay);
    btnSortName = new QPushButton("Sort by Denumire");
    btnSortOre = new QPushButton("Sort by Ore");
    lay->addWidget(btnSortName);
    lay->addWidget(btnSortOre);

    l_left->addWidget(wdg);

        QWidget *flt_btn=new QWidget;
        QHBoxLayout *flt_lay=new QHBoxLayout;
        flt_btn->setLayout(flt_lay);
    
        btnFilterOre=new QPushButton("Filtrare dupa ore");
        btnFilterCadru=new QPushButton("Filtrare dupa cadru");
        btn_reset = new QPushButton("Reset order");

        flt_lay->addWidget(btn_reset);
        flt_lay->addWidget(btnFilterOre);
        flt_lay->addWidget(btnFilterCadru);
    
        l_left->addWidget(flt_btn);

    lyMain->addWidget(w_left);

    //form pentru detalii
    QWidget* w_right = new QWidget;
    QVBoxLayout* lay_right = new QVBoxLayout;
    w_right->setLayout(lay_right);

    QWidget* form = new QWidget;
    QFormLayout* lay_form = new QFormLayout;
    form->setLayout(lay_form);
    QLabel* denumire = new QLabel("Denumire");
    txtDenumire = new QLineEdit;
    QLabel* ore = new QLabel("Numar de ore");
    txtOre = new QLineEdit;
    QLabel* tip = new QLabel("Tip");
    txtTip = new QLineEdit;
    QLabel* cadru = new QLabel("Cadru");
    txtCadru = new QLineEdit;
    QLabel* filtrare1 = new QLabel("Nr ore de filtrat");
    txtFilterOre = new QLineEdit;
    QLabel* filtrare2 = new QLabel("Cadru de filtrat");
    txtFilterCadru = new QLineEdit;

    lay_form->addRow(denumire, txtDenumire);
    lay_form->addRow(ore, txtOre);
    lay_form->addRow(tip, txtTip);
    lay_form->addRow(cadru, txtCadru);
    lay_form->addRow(filtrare1, txtFilterOre);
    lay_form->addRow(filtrare2, txtFilterCadru);

    lay_right->addWidget(form);

    QWidget* but_zone = new QWidget;
    QVBoxLayout* lay_but = new QVBoxLayout;
    but_zone->setLayout(lay_but);

    btn_add = new QPushButton("Add");
    lay_but->addWidget(btn_add);

    QWidget* sec_but = new QWidget;
    QHBoxLayout* sec_lay = new QHBoxLayout;
    sec_but->setLayout(sec_lay);

    btn_del = new QPushButton("Delete");
    btn_mod = new QPushButton("Update");
    sec_lay->addWidget(btn_del);
    sec_lay->addWidget(btn_mod);

    lay_but->addWidget(sec_but);

    btn_undo = new QPushButton("Undo");
    lay_but->addWidget(btn_undo);


    btn_lst_mst = new QPushButton("Generate List Master");
    lay_but->addWidget(btn_lst_mst);
    btn_lst_rdonly = new QPushButton("Generate List Read-Only");
    lay_but->addWidget(btn_lst_rdonly);




    lay_right->addWidget(but_zone);

    lyMain->addWidget(w_right);
    lb_index = -1;

    opt_but = new QWidget;
    lay_opt = new QVBoxLayout;
    opt_but->setLayout(lay_opt);
    lyMain->addWidget(opt_but);

   

    //QTableWidget* tabel = new QTableWidget;
   
}


void GUI::connectSignalsSlots() {
    //QObject::connect(tabel, &QTableWidget::cellClicked, [=]() {
    //    auto sel = tabel->selectedItems();
    //    if (sel.empty()) {
    //        txtDenumire->setText("");
    //        txtOre->setText("");
    //        txtTip->setText("");
    //        txtCadru->setText("");
    //    }
    //    else {
    //        auto sel_item = sel.at(0);
    //        auto name = sel_item->text().toStdString();
    //        //auto cadru = sel_item->data(Qt::UserRole).toString();
    //        Disciplina to_print;
    //         lb_index = 0;
    //        for (const auto& dis : srv.getAllDiscipline()) {
    //            if (dis.getDenumire() == name) {
    //                to_print = dis;
    //                break;
    //            }
    //            ++lb_index;
    //        }
    //        txtDenumire->setText(QString::fromStdString(to_print.getDenumire()));
    //        txtCadru->setText(QString::fromStdString(to_print.getCadru()));
    //        txtTip->setText(QString::fromStdString(to_print.getTip()));
    //        txtOre->setText(QString::number(to_print.getOre()));
    //    }
    //    });

    QObject::connect(btnSortName, &QPushButton::clicked, [&]() {
        vector<Disciplina> dis;
        dis.resize(srv.getAllDiscipline().size());
        srv.sortByDenumire(dis);
        reloadList(dis);
        });

    QObject::connect(btnSortOre, &QPushButton::clicked, [&]() {
        vector<Disciplina> dis;
        dis.resize(srv.getAllDiscipline().size());
        srv.sortbyore(dis);
        reloadList(dis);
        });



    QObject::connect(btn_reset, &QPushButton::clicked, [=]() {
        reloadList(srv.getAllDiscipline());
        reset_form();
        });

    QObject::connect(btnFilterOre, &QPushButton::clicked, [=]() {
        string val_str = txtFilterOre->text().toStdString();
        try {
            vector<Disciplina> rez;
            rez.clear();
            srv.filtrareOre(val_str, rez);
            reloadList(rez);
        }
        catch (ContractRepoException& re) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(toMyString(re.msg)));
        }
        });

    QObject::connect(btnFilterCadru, &QPushButton::clicked, [=]() {
        string val_str = txtFilterCadru->text().toStdString();
        try {
            vector<Disciplina> rez;
            rez.clear();
            srv.filtrareCadru(val_str, rez);
            reloadList(rez);
        }
        catch (ContractRepoException& re) {
            QMessageBox::warning(this, "Warning", QString::fromStdString(toMyString(re.msg)));
        }
        });

    QObject::connect(btn_lst_mst, &QPushButton::clicked, [=]() {
        auto wind = new ListaGUI{ rep,srv };
        rcp.push_back(wind);
        wind->show();
        });

    QObject::connect(btn_lst_rdonly, &QPushButton::clicked, [=]() {
        auto wind = new PaintGUI{ rep };
        pg.push_back(wind);
        wind->show();
        });

    QObject::connect(lst_view->selectionModel(), &QItemSelectionModel::selectionChanged, [=]() {
        auto sel = lst_view->selectionModel();
        if (sel->selectedIndexes().empty()) {
            txtDenumire->setText("");
            txtOre->setText("");
            txtTip->setText("");
            txtCadru->setText("");
            return;
        }
        auto sel_index = sel->selectedIndexes().at(0).row();
        auto elem = act_list[sel_index];
        auto name = lst_view->model()->data(lst_view->model()->index(sel_index, 0), Qt::DisplayRole).toString();
        lb_index = sel_index;
        txtDenumire->setText(name);
        txtOre->setText(QString::number(elem.getOre()));
        txtTip->setText(QString::fromStdString(elem.getTip()));
        txtCadru->setText(QString::fromStdString(elem.getCadru()));
        });


    QObject::connect(btn_add, &QPushButton::clicked, this, &GUI::addMed);
    QObject::connect(btn_del, &QPushButton::clicked, this, &GUI::delMed);
    QObject::connect(btn_mod, &QPushButton::clicked, this, &GUI::uptMed);
    QObject::connect(btn_undo, &QPushButton::clicked, this, &GUI::undoGUI);
}

void GUI::clearLayout(QLayout* layout)
{
    if (layout == NULL)
        return;
    QLayoutItem* item;
    while ((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}
void GUI::updateBut(vector<Disciplina>& all) {


    clearLayout(lay_opt);
    set<string> unique;



    for (const auto& dis : srv.getAllDiscipline()) {
        unique.insert(dis.getCadru());
    }

    disciplina_but.clear();

    for (auto& it : unique) {
        disciplina_but.push_back(new QPushButton(QString::fromStdString(it)));
    }

    for (auto btn : disciplina_but) {
        lay_opt->addWidget(btn);
        QObject::connect(btn, &QPushButton::clicked, [=]() {
            auto val = btn->text().toStdString();
            int nr = 0;
            for (const auto& dis : srv.getAllDiscipline()) {
                if (dis.getCadru() == val) {
                    ++nr;
                }
            }
            QMessageBox::information(nullptr, "Info", QString::number(nr));
            });
    }
}

void GUI::reloadList(vector<Disciplina>& dis) {
    
    act_list = dis;
    model->setDisciplina(dis);
    
    
    
    
    
    /*tabel->clear();
    tabel->setColumnCount(2);
    tabel->setRowCount(dis.size());
    int i=0;
    for(const auto&  med :dis){
        QTableWidgetItem *item=new QTableWidgetItem(QString::fromStdString(med.getDenumire()));
        QTableWidgetItem *item1=new QTableWidgetItem(QString::fromStdString(med.getCadru()));
        tabel->setItem(i,0,item);
        tabel->setItem(i,1,item1);
        ++i;
    }*/

}

void GUI::addMed() {
    try {
        srv.addDisciplina(txtDenumire->text().toStdString(), txtOre->text().toInt(),txtTip->text().toStdString(), txtCadru->text().toStdString());
        reloadList(srv.getAllDiscipline());
    }
    catch (ValidationException& ve) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(toMyString(ve.msg)));
    }
    catch (ContractRepoException& re) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(toMyString(re.msg)));
    }
    updateBut(srv.getAllDiscipline());
}

void GUI::delMed() {
    auto denumire = txtDenumire->text().toStdString();
    auto tip = txtTip->text().toStdString();
    auto cadru = txtCadru->text().toStdString();
    auto ore = txtOre->text().toInt();
    auto d = Disciplina(denumire,ore,tip,cadru);
    int index = 0;
    for (auto& dis : srv.getAllDiscipline()) {
        if (dis == d) {
            break;
        }
        ++index;
    }
    if (index == srv.getAllDiscipline().size()) {
        QMessageBox::warning(this, "Warning", QString::fromStdString("Nu exista elementul introdus"));
    }
    else {
        srv.delDisciplina(index);
        reloadList(srv.getAllDiscipline());
        updateBut(srv.getAllDiscipline());
    }

}

void GUI::uptMed() {
    auto denumire = txtDenumire->text().toStdString();
    auto tip = txtTip->text().toStdString();
    auto cadru = txtCadru->text().toStdString();
    auto ore = txtOre->text().toInt();
    int index = 0;
    for (auto& dis : srv.getAllDiscipline()) {
        if (dis.getDenumire() == denumire)
        {
            break;
        }
        ++index;
    }
    if (index == srv.getAllDiscipline().size()) {
        QMessageBox::warning(this, "Warning", QString::fromStdString("Nu ati selectat nici-un element"));
        return;
    }

    try {
        srv.modifyDisciplina(index, denumire, ore, tip, cadru);
        reloadList(srv.getAllDiscipline());
        updateBut(srv.getAllDiscipline());
    }
    catch (ValidationException& ve) {
        QMessageBox::warning(this, "Warning", QString::fromStdString(toMyString(ve.msg)));
    }
    



}

void GUI::undoGUI() {

    srv.undo();
    reloadList(srv.getAllDiscipline());
    updateBut(srv.getAllDiscipline());
 
}


void GUI::reset_form() {
    txtDenumire->setText("");
    txtOre->setText("");
    txtTip->setText("");
    txtCadru->setText("");
}

void ListaGUI::initGUI() {
    setLayout(recipe_main_layout);

    recipe_lst = new QListWidget;
    recipe_main_layout->addWidget(recipe_lst);

    QWidget* recipe_but_zone = new QWidget;
    QVBoxLayout* recipe_but_layout = new QVBoxLayout;
    recipe_but_zone->setLayout(recipe_but_layout);

    QWidget* recipe_form = new QWidget;
    QFormLayout* recipe_form_layout = new QFormLayout;
    recipe_form->setLayout(recipe_form_layout);

    QLabel* lbl_recipe = new QLabel("Input");
    lne_recipe = new QLineEdit;

    recipe_form_layout->addRow(lbl_recipe, lne_recipe);

    recipe_but_layout->addWidget(recipe_form);

    add_to_rec = new QPushButton("Add");
    empty_rec = new QPushButton("Empty list");
    random_add = new QPushButton("Add random");
    export_recipe = new QPushButton("Export");
    help_button = new QPushButton("Help");

    recipe_but_layout->addWidget(add_to_rec);
    recipe_but_layout->addWidget(empty_rec);
    recipe_but_layout->addWidget(random_add);
    recipe_but_layout->addWidget(export_recipe);
    recipe_but_layout->addWidget(help_button);

    recipe_main_layout->addWidget(recipe_but_zone);

    reloadDis(rep.getallContractDiscipline());
}

void ListaGUI::reloadDis(vector<Disciplina> dis) {
    recipe_lst->clear();
    for (const auto& med : dis) {
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(med.getDenumire()));
        recipe_lst->addItem(item);
    }
}

void ListaGUI::connectSignals() {
    QObject::connect(add_to_rec, &QPushButton::clicked, [=]() {
        auto inp = lne_recipe->text().toStdString();
        int nr = 0;
        bool valid = true;
        for (auto& ch : inp) {
            if ('0' <= ch && ch <= '9') {
                nr = nr * 10 + (ch - '0');
            }
            else {
                valid = false;
            }
        }
        if (nr > srv.getAllDiscipline().size()) {
            valid = false;
        }
        if (valid) {
            rep.addDisciplinatoLista(srv.getAllDiscipline()[nr]);
            reloadDis(rep.getallContractDiscipline());
        }
        else {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Index invalid"));
        }
        });

    QObject::connect(empty_rec, &QPushButton::clicked, [=]() {
        rep.emptyList();
        reloadDis(rep.getallContractDiscipline());
        //reset_form();
        });

    QObject::connect(random_add, &QPushButton::clicked, [=]() {
        auto inp = lne_recipe->text().toStdString();
        int nr = 0;
        bool valid = true;
        for (auto& ch : inp) {
            if ('0' <= ch && ch <= '9') {
                nr = nr * 10 + (ch - '0');
            }
            else {
                valid = false;
            }
        }
        if (valid) {
            rep.addRandomDisciplina(srv.getAllDiscipline(), nr);
            reloadDis(rep.getallContractDiscipline());
        }
        else {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Numar invalid"));
        }
        });

    QObject::connect(export_recipe, &QPushButton::clicked, [=]() {
        auto filename = lne_recipe->text().toStdString();
        rep.save_to_file(filename);
        });

    QObject::connect(help_button, &QPushButton::clicked, [=]() {
        string msg = "Campul input se foloseste pentru a comunica optiunile\n";
        msg += "Pentru Add in input se va specifica indicele de adaugat\n";
        msg += "Pentru Add random in input se va specifica numarul de entitati de adaugat\n";
        msg += "Pentru Export in input se va specifica numele fisierului in care se face exportul\n";
        QMessageBox::information(this, "Help", QString::fromStdString(msg));
        });
}


