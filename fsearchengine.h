#ifndef FSEARCHENGINE_H
#define FSEARCHENGINE_H

#include <QObject>

class FSearchEngine : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList searchData READ searchData WRITE setSearchData)
    Q_PROPERTY(QStringList searchResult READ searchResult)

public:
    explicit FSearchEngine(QObject *parent = Q_NULLPTR);

    void setSearchData(QStringList data);

    QStringList searchData();

    QStringList searchResult();

signals:

    void searchingStarted();

    void searchingFinished();

public slots:

    void search(QString searchInput);

private:

    QStringList m_searchData;
    QStringList m_searchResult;

};

#endif // FSEARCHENGINE_H
