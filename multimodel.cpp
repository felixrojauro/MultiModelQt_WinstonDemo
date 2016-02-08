#include "multimodel.h"

BaseData::BaseData(QObject *parent) : QObject(parent) {}
BaseData::~BaseData() {}

BaseData::BaseData(const BaseData &s) : QObject( s.parent() )
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
{    Q_UNUSED( parent); return model.size(); }

QVariant SingleModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid()) return QVariant();
    if(role == value)  return QVariant(model[index.row()].value);
    if(role == type)  return QVariant(model[index.row()].type);
    if(role == colorTest) return QVariant(model[index.row()].colorTest);
	return QVariant();
}

bool SingleModel::setData(const QModelIndex& a_rIndex, const QVariant& a_rValue, int a_iRole)
{
	if ( a_rIndex.isValid() && a_iRole > Qt::UserRole )
	{
		BaseData item = model.at( a_rIndex.row() );
		if(a_iRole == value)  item.value = a_rValue.toDouble();
		else if(a_iRole == type)  item.type = a_rValue.toString();
		else if(a_iRole == colorTest)  item.colorTest = a_rValue.toBool();
		else
		{
			return false;
		}
		emit dataChanged( a_rIndex, a_rIndex );
		return true;
	}
	return false;
}

QHash<int, QByteArray> SingleModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[value] = "value";
    roles[type]  = "type";
    roles[colorTest] = "colorTest";
    return roles;
}

SingleModel::SingleModel(const SingleModel &m) : QAbstractListModel(m.parent())
{    *this = m; }

SingleModel& SingleModel::operator =(const SingleModel &m)
{
    model = m.model;
    return *this;
}



MultiModel::MultiModel(QObject *parent) : QObject(parent), m_model1( 0 ), m_model2( 0 )
{
//    loadModel1();
//    loadModel2();
//    qDebug() << "Loaded both models";
}

MultiModel::~MultiModel() {}

MultiModel::MultiModel(const MultiModel &m) : QObject(m.parent())
{    *this = m; }

MultiModel& MultiModel::operator =(const MultiModel &m)
{
    m_model1 = m.m_model1;
    m_model2 = m.m_model2;
    return *this;
}

SingleModel* MultiModel::model1() const { return m_model1; }
void MultiModel::setModel1(SingleModel* m) { m_model1 = m; emit model1Changed(); }
SingleModel* MultiModel::model2() const { return m_model2; }
void MultiModel::setModel2(SingleModel* m) { m_model2 = m; emit model2Changed(); }


void MultiModel::loadModel1()
{
	if ( !m_model1 )
		m_model1 = new SingleModel(this);
	emit model1Changed();
	m_model1->model.resize(9);
    for (int i=0; i<9; i++) {
		m_model1->model[i].type = "M1 prop";
		m_model1->model[i].type.append(QString::number(i));
		m_model1->model[i].value = i;
		m_model1->model[i].colorTest = true;
		QModelIndex index = m_model1->CreateIndex(i,0);
		emit m_model1->dataChanged( index, index);
    }
	emit model1Changed();
	qDebug() << "Loaded model1";
}

void MultiModel::loadModel2()
{
	if ( !m_model2 )
		m_model2 = new SingleModel(this);
	emit model2Changed();
	m_model2->model.resize(9);
    for (int i=0; i<9; i++) {
		m_model2->model[i].type = "M2 prop";
		m_model2->model[i].type.append(QString::number(i));
		m_model2->model[i].value = i * 11;
		m_model2->model[i].colorTest = false;
		QModelIndex index = m_model2->CreateIndex(i,0);
		emit m_model2->dataChanged( index, index);
	}
	emit model2Changed();
	qDebug() << "Loaded model2";
}
