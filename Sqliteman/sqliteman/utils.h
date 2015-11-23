/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#ifndef UTILS_H
#define UTILS_H

#include <QCoreApplication>

#include "sqlparser.h"

class QComboBox;
class QItemSelection;
class QTreeWidgetItem;
class QTextEdit;
class QIcon;
class QPixmap;
class QSqlError;
class QSqlRecord;
class QLineEdit;
class QTableView;

//! Various helper functions
namespace Utils {
	
/*! A set of helper functions for simpler code
*/
QIcon getIcon(const QString & fileName);
QPixmap getPixmap(const QString & fileName);

QString getTranslator(const QString & localeName);

//! \brief Check if the object tree should be refilled depending on sql statement
bool updateObjectTree(const QString & sql);

//! \brief Check if the current table may have changed depending on sql statement
bool updateTables(const QString & sql);

//! \brief Quote identifier for generated SQL statement
QString quote(QString s);

/*! \brief BackQuote identifier for generated SQL statement - needed because in
		   some contexts quoted identifiers are treated as string literals if
		   they don't match a column name. */
QString backQuote(QString s);

//! \brief Quote list of identifiers for generated SQL statement
QString quote(QStringList l);

//! \brief BackQuote list of identifiers for generated SQL statement
QString backQuote(QStringList l);

QString literal(QString s);

QString unQuote(QString s);

QString like(QString s);

void setColumnWidths(QTableView * tv);

//debugging hacks
void dump(QString s);
void dump(QItemSelection selection);
void dump(QTreeWidgetItem & item);
void dump(QTreeWidgetItem * item);
void dump(QComboBox & box);
void dump(QComboBox *box);
void dump(QStringList sl);
void dump(QList<int> il);
void dump(QTextEdit & te);
void dump(QTextEdit * te);
QString variantToString(QVariant x);
void dump(QVariant x);
void dump(QSqlRecord & rec);
void dump(QLineEdit & le);
void dump(QLineEdit * le);
void dump(QSqlError & e);
void dump(QSqlError * e);
void dump(Token & t);
void dump(QList<Token> tl);
void dump(Expression * e);
void dump(FieldInfo f);
void dump(QList<FieldInfo> fl);
void dump(SqlParser & p);
void dump(SqlParser * pp);
void dump(QList<SqlParser> pl);
void dump(QMap<QString,QString> map);
};

#endif
