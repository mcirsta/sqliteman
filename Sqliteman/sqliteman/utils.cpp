/*
For general Sqliteman copyright and licensing information please refer
to the COPYING file provided with the program. Following this notice may exist
a copyright and/or license notice that predates the release of Sqliteman
for which a new license (GPL+exception) is in place.
*/

#include <QIcon>
#include <QPixmapCache>

#include "utils.h"


QIcon Utils::getIcon(const QString & fileName)
{
	QPixmap pm;

	if (! QPixmapCache::find(fileName, &pm))
	{
		QPixmap npm(QString(ICON_DIR) + "/" + fileName);
		QPixmapCache::insert(fileName, npm);
		return npm;
	}

	return pm;
}

QPixmap Utils::getPixmap(const QString & fileName)
{
	return QPixmap(QString(ICON_DIR) + "/" + fileName);
}

QString Utils::getTranslator(const QString & localeName)
{
	return QString("%1/sqliteman_%2.qm").arg(TRANSLATION_DIR).arg(localeName);
}

bool Utils::updateObjectTree(const QString & sql)
{
	if (sql.isNull())
		return false;
	QString tmp(sql.trimmed().toUpper());
	if (tmp.left(4) == "DROP" || tmp.left(6) == "CREATE" || tmp.left(5) == "ALTER")
		return true;
	return false;
}

QString Utils::quote(QString s)
{
	return "\"" + s.replace("\"", "\"\"") + "\"";
}

QString Utils::quote(QStringList l)
{
	foreach (QString s, l) { s.replace("\"", "\"\""); }
	return "\"" + l.join("\", \"") + "\"";
}

QString Utils::literal(QString s)
{
	return "'" + s.replace("'", "''") + "'";
}

QString Utils::unQuote(QString s)
{
	if (s.startsWith("'")) {
		s.replace("''", "'");
		return s.mid(1, s.size() - 2);
	}
	else if (s.startsWith("\"")) {
		s.replace("\"\"", "\"");
		return s.mid(1, s.size() - 2);
	}
	else { return s; }
}

QString Utils::like(QString s)
{
	return "'%" + s.replace("'", "''") + "%'";
}
