#include <qsql.h>
#include <qsqldatabase.h>
#include <qstringlist.h>
#include <iostream>
#include <qapplication.h>
#include "src/svnqt/cache/LogCache.hpp"

#include "src/svnqt/cache/test/testconfig.h"

int main(int argc,char**argv)
{
    QApplication app(argc,argv);
    QStringList list = QSqlDatabase::drivers();
    QStringList::Iterator it = list.begin();
    while( it != list.end() ) {
        std::cout << (*it) << std::endl;
        ++it;
    }
    svn::cache::LogCache a(TESTDBPATH);
    return 0;
}