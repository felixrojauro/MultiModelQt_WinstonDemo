#include "multimodel.h"

BaseData::BaseData(QObject *parent) : QObject(parent) {}
BaseData::~BaseData() {}

BaseData::BaseData(const BaseData &s)
{    *this = s; }

BaseData& BaseData::operator=(const BaseData &s)
{
    value = s.value;
    type = s.type;
    colorTest = s.colorTest;
    return *this;
}


SingleModel::SingleModel(QObject *parent) : QAbstractListModel(parent)
{
    model.resize(9);
    for (int i=0; i<9; i++) {
        model[i].type = "M0 prop";
        model[i].type.append(QString::number(i));
        model[i].value = i;
        model[i].colorTest = (i % 2 ==0);
    }

//    for (int i=0; i<9; i++) {
//        qDebug() << model[i].type << " value = " << model[i].value << " colorTest = " << model[i].colorTest;
//    }
}

int SingleModel::rowCount(const QModelIndex &parent) const
{    return model.size(); }

QVariant SingleModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();
    if(role == value)  return QVariant(model[index.row()].value);
    if(role == type)  return QVariant(model[index.row()].type);
    if(role == colorTest) return QVariant(model[index.row()].colorTest);
    return QVariant();
}

QHash<int, QByteArray> SingleModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[value] = "value";
    roles[type]  = "type";
    roles[colorTest] = "colorTest";
    return roles;
}

SingleModel::SingleModel(const SingleModel &m)
{    *this = m; }

SingleModel& SingleModel::operator =(const SingleModel &m)
{
    model = m.model;
    return *this;
}



MultiModel::MultiModel(QObject *parent) : QObject(parent)
{
    loadModel1();
    loadModel2();
    qDebug() << "Loaded both models";
}

MultiModel::~MultiModel() {}

MultiModel::MultiModel(const MultiModel &m)
{    *this = m; }

MultiModel& MultiModel::operator =(const MultiModel &m)
{
    m_model1 = m.m_model1;
    m_model2 = m.m_model2;
    return *this;
}

SingleModel MultiModel::model1() const { return m_model1; }
void MultiModel::setModel1(const SingleModel &m) { m_model1 = m; }
SingleModel MultiModel::model2() const { return m_model2; }
void MultiModel::setModel2(const SingleModel &m) { m_model2 = m; }


void MultiModel::loadModel1()
{
    m_model1.model.resize(9);
    for (int i=0; i<9; i++) {
        m_model1.model[i].type = "M1 prop";
        m_model1.model[i].type.append(QString::number(i));
        m_model1.model[i].value = i;
        m_model1.model[i].colorTest = true;
    }
}

void MultiModel::loadModel2()
{
    m_model2.model.resize(9);
    for (int i=0; i<9; i++) {
        m_model1.model[i].type = "M2 prop";
        m_model1.model[i].type.append(QString::number(i));
        m_model1.model[i].value = i * 11;
        m_model1.model[i].colorTest = false;
    }
}
