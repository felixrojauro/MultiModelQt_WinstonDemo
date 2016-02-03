#ifndef MULTIMODEL_H
#define MULTIMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QVariant>
#include <QString>
#include <QVector>
#include <vector>
#include <QHash>
#include <QT>
#include <QDebug>

class BaseData : public QObject {   // base data structure for most models
    Q_OBJECT
public:
    BaseData(QObject *parent = 0);
    ~BaseData();
    BaseData(const BaseData &s);
    BaseData& operator =(const BaseData &s);

    double value;
    QString type;
    bool colorTest;
};

class SingleModel : public QAbstractListModel {
    Q_OBJECT
public:
    enum singleRoles {
    value = Qt::UserRole + 1,
    type,
    colorTest
    };
    explicit SingleModel(QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;

    SingleModel(const SingleModel &m);
    SingleModel& operator =(const SingleModel &m);
//private:
    //QVector<BaseData> model;
    std::vector<BaseData> model;
};

class MultiModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(SingleModel model1 READ model1 WRITE setModel1 NOTIFY model1Changed)
    Q_PROPERTY(SingleModel model2 READ model2 WRITE setModel2 NOTIFY model2Changed)

public:
    MultiModel(QObject *parent = 0);
    ~MultiModel();
    MultiModel(const MultiModel &m);
    MultiModel& operator =(const MultiModel &m);

    SingleModel model1() const;
    void setModel1(const SingleModel &m);
    SingleModel model2() const;
    void setModel2(const SingleModel &m);

private:
    SingleModel m_model1, m_model2;
    void loadModel1();
    void loadModel2();

signals:
    void model1Changed();
    void model2Changed();
};

Q_DECLARE_METATYPE(BaseData)
Q_DECLARE_METATYPE(SingleModel)
Q_DECLARE_METATYPE(MultiModel)
//Q_DECLARE_SEQUENTIAL_CONTAINER_METATYPE(SingleModel)

#endif // MULTIMODEL_H
