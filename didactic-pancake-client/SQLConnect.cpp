#include "SQLConnect.h"

#include <QDebug>
#include <QApplication>
#include <QDir>

using namespace std;

SQLConnect *SQLConnect::getInstance()
{
    static SQLConnect SQLConn;
    return &SQLConn;
}

vector<tuple<long long, int, long long, QString, int>> SQLConnect::getNlinesChatRecord(const QString &user, int fromNum, int num)
{
    vector<tuple<long long, int, long long, QString, int>> res;
    if (!m_database.open())
    {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    }
    else
    {
        QSqlQuery sql_query(m_database);
        QString select_sql = "SELECT * FROM (SELECT * FROM message_tb WHERE user_name = ?) ORDER BY timestamp DESC limit ? OFFSET ?";
        sql_query.prepare(select_sql);
        sql_query.addBindValue(user);
        sql_query.addBindValue(num);
        sql_query.addBindValue(fromNum);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            while (sql_query.next())
            {
                long long id = sql_query.value(0).toLongLong();
                QString name = sql_query.value(1).toString();
                int isMine = sql_query.value(2).toInt();
                long long timestp = sql_query.value(3).toLongLong();
                QString text = sql_query.value(4).toString();
                int isSend = sql_query.value(5).toInt();
                // qDebug()<<QString("%1,%2,%3,%4,%5,%6").arg(id).arg(name).arg(isMine).arg(timestp).arg(text).arg(isSend);
                res.emplace_back(make_tuple(id, isMine, timestp, text, isSend));
            }
        }

        sql_query.finish();
    }
    m_database.close();

    reverse(res.begin(), res.end());
    return res;
}

void SQLConnect::addChatRecord(long long id, const QString &user, int isMine, long long timestp, const QString &content, int isSend)
{
    if (!m_database.open())
    {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    }
    else
    {
        QSqlQuery sql_query(m_database);
        QString select_sql = "INSERT INTO message_tb VALUES(?,?,?,?,?,?)";
        sql_query.prepare(select_sql);
        sql_query.addBindValue(id);
        sql_query.addBindValue(user);
        sql_query.addBindValue(isMine);
        sql_query.addBindValue(timestp);
        sql_query.addBindValue(content);
        sql_query.addBindValue(isSend);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }

        sql_query.finish();
    }
    m_database.close();
}

void SQLConnect::initUserDataConnect(const QString &username)
{
    if (QSqlDatabase::contains("qt_sql_default_connection"))
    {
        m_database = QSqlDatabase::database("qt_sql_default_connection");
    }
    else
    {
        m_database = QSqlDatabase::addDatabase("QSQLITE");

        // 判断文件夹是否存在，不存在则创建
        QDir dir(QApplication::applicationDirPath() + "/" + username);
        if (!dir.exists())
        {
            bool ismkdir = dir.mkdir(QApplication::applicationDirPath() + "/" + username);
            if (!ismkdir)
                qDebug() << "Create path fail" << endl;
            else
                qDebug() << "Create fullpath success" << endl;
        }

        m_database.setDatabaseName(QApplication::applicationDirPath() + "/" + username + "/UserDatas.db");
        m_database.setUserName("root");
        m_database.setPassword("123456");

        if (!m_database.open())
        {
            qDebug() << "Error: Failed to connect database." << m_database.lastError();
        }
        else
        {
            QSqlQuery sql_query(m_database);
            QString create_sql = "CREATE TABLE IF NOT EXISTS message_tb(message_id BIGINT PRIMARY KEY,user_name VARCHAR(16),is_mine TINYINT,timestamp BIGINT,text TEXT,is_send TINYINT)";
            sql_query.prepare(create_sql);
            if (!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }

            create_sql = "CREATE TABLE IF NOT EXISTS chat_list_tb(user_name VARCHAR(16) PRIMARY KEY,last_time BIGINT,unread_num INT,content TEXT,is_show TINYINT)";
            sql_query.prepare(create_sql);
            if (!sql_query.exec())
            {
                qDebug() << sql_query.lastError();
            }

            sql_query.finish();
        }
        m_database.close();
    }
}

void SQLConnect::setChatRecordisSend(long long id, int isSend)
{
    if (!m_database.open())
    {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    }
    else
    {
        QSqlQuery sql_query(m_database);
        QString update_sql = "UPDATE message_tb SET is_send = ? WHERE message_id = ?";
        sql_query.prepare(update_sql);
        sql_query.addBindValue(isSend);
        sql_query.addBindValue(id);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }

        sql_query.finish();
    }
    m_database.close();
}

int SQLConnect::getUserChatRecordNumber(const QString &username)
{
    int res = 0;
    if (!m_database.open())
    {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    }
    else
    {
        QSqlQuery sql_query(m_database);
        QString select_sql = "SELECT COUNT(*) FROM message_tb WHERE user_name = ?";
        sql_query.prepare(select_sql);
        sql_query.addBindValue(username);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            while (sql_query.next())
            {
                res = sql_query.value(0).toInt();
            }
        }
        sql_query.finish();
    }
    m_database.close();

    return res;
}

void SQLConnect::deleteChatRecord(const QString &username)
{
    if (!m_database.open())
    {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    }
    else
    {
        QSqlQuery sql_query(m_database);
        QString select_sql = "DELETE FROM message_tb WHERE user_name = ?";
        sql_query.prepare(select_sql);
        sql_query.addBindValue(username);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        sql_query.finish();
    }
    m_database.close();
}

vector<tuple<QString, long long, int, QString, int>> SQLConnect::getChatItem()
{
    vector<tuple<QString, long long, int, QString, int>> res;
    if (!m_database.open())
    {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    }
    else
    {
        QSqlQuery sql_query(m_database);
        QString select_sql = "SELECT * FROM chat_list_tb";
        sql_query.prepare(select_sql);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            while (sql_query.next())
            {
                QString userName = sql_query.value(0).toString();
                long long lastTime = sql_query.value(1).toLongLong();
                int unReadNum = sql_query.value(2).toInt();
                QString content = sql_query.value(3).toString();
                int isShow = sql_query.value(4).toInt();
                res.emplace_back(make_tuple(userName, lastTime, unReadNum, content, isShow));
            }
        }

        sql_query.finish();
    }
    m_database.close();

    return res;
}

int SQLConnect::getAllunReadNum()
{
    int res = 0;
    if (!m_database.open())
    {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    }
    else
    {
        QSqlQuery sql_query(m_database);
        QString select_sql = "SELECT SUM(unread_num) FROM chat_list_tb WHERE is_show = 1";
        sql_query.prepare(select_sql);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        else
        {
            while (sql_query.next())
            {
                res = sql_query.value(0).toInt();
            }
        }

        sql_query.finish();
    }
    m_database.close();

    return res;
}

void SQLConnect::addChatItem(const QString &username, long long lastTime, int unreadNum, const QString &content, int isShow)
{
    if (!m_database.open())
    {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    }
    else
    {
        QSqlQuery sql_query(m_database);
        QString select_sql = "INSERT OR IGNORE INTO chat_list_tb VALUES(?,?,?,?,?)";
        sql_query.prepare(select_sql);
        sql_query.addBindValue(username);
        sql_query.addBindValue(lastTime);
        sql_query.addBindValue(unreadNum);
        sql_query.addBindValue(content);
        sql_query.addBindValue(isShow);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }

        sql_query.finish();
    }
    m_database.close();
}

void SQLConnect::setChatItem(const QString &username, long long lastTime, int unreadNum, const QString &content, int isShow)
{
    if (!m_database.open())
    {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    }
    else
    {
        QSqlQuery sql_query(m_database);
        QString update_sql = "UPDATE chat_list_tb SET last_time = ?, unread_num = ?, content = ?, is_show = ? WHERE user_name = ?";
        sql_query.prepare(update_sql);
        sql_query.addBindValue(lastTime);
        sql_query.addBindValue(unreadNum);
        sql_query.addBindValue(content);
        sql_query.addBindValue(isShow);
        sql_query.addBindValue(username);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }

        sql_query.finish();
    }
    m_database.close();
}

void SQLConnect::deleteChatItem(const QString &username)
{
    if (!m_database.open())
    {
        qDebug() << "Error: Failed to connect database." << m_database.lastError();
    }
    else
    {
        QSqlQuery sql_query(m_database);
        QString delete_sql = "DELETE FROM chat_list_tb WHERE user_name = ?";
        sql_query.prepare(delete_sql);
        sql_query.addBindValue(username);
        if (!sql_query.exec())
        {
            qDebug() << sql_query.lastError();
        }
        sql_query.finish();
    }
    m_database.close();
}

SQLConnect::SQLConnect()
{
}
