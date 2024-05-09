#include "database.h"

database *database::p_instance = nullptr;
databaseDestroyer database::destroyer;

QByteArray database::sendQuerry(const QString& text, const QVariantList& queryParams)
{
    QSqlQuery query(db);
    query.prepare(text);

    for (int i = 0; i < queryParams.size(); ++i) {
        query.bindValue(i, queryParams.at(i));
    }

    if (!query.exec()) {
        qDebug() << "Error executing query: " << query.lastError().text();
        return QByteArray(  );
    }
    QString result;
    while (query.next()) {
        for (int i = 0; i < query.record().count(); i++) {
            result += query.value(i).toString().toUtf8();
            if (i < query.record().count() - 1) {
                result += "\t";
            }
        }
        result += "\n";
    }

    return result.toUtf8();
}


