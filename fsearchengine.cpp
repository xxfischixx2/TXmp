#include "fsearchengine.h"

FSearchEngine::FSearchEngine(QObject *parent) : QObject(parent)
{

}

void FSearchEngine::setSearchData(QStringList data)
{

    m_searchData.clear();
    m_searchData = data;
}

QStringList FSearchEngine::searchData()
{

    return m_searchData;
}

QStringList FSearchEngine::searchResult()
{
    return searchResult();
}

void FSearchEngine::search(QString searchInput)
{

    emit searchingStarted();

    QStringList words;

    for(int i = 0;i < searchInput.length();i++){

        if(searchInput[i].isLetter()){

            words[words.length() - 1].append(searchInput[i]);
        }

        else if(!searchInput[i].isLetter() && words[words.length() - 1] != ""){

            words.append("");
        }

    }

    m_searchResult.clear();
    words.append(searchInput);

    for(int z = 0;z < words.length();z++){

        for(int i = 0;i < m_searchData.length();i++){

            for(int n = 0;n < m_searchData[i].length() - (words[z].length() - 1);n++){

                if(m_searchData[i][n] == words[z]){

                    m_searchResult.append(m_searchData[i]);
                    break;
                }

            }

        }

    }

    emit searchingFinished();
}
