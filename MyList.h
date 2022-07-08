#pragma once

#include <QAbstractTableModel>
#include "Disciplina.h"
#include <vector>

using std::vector;

class MyListModel :public QAbstractListModel {
    vector<Disciplina> dis;
public:
    MyListModel(const vector<Disciplina>& di) : dis{ di} {}


    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return dis.size();
    }

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            auto med = dis[index.row()].getDenumire();
            return QString::fromStdString(med);
        }
        return QVariant{};
    }

    void setDisciplina(vector<Disciplina>& d) {
        dis = d;
        auto topIndex = createIndex(0, 0);
        auto botIndex = createIndex(rowCount(), 0);
        emit dataChanged(topIndex, botIndex);
    }
};