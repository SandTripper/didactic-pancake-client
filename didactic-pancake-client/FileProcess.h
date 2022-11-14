#ifndef FILEPROCESS_H
#define FILEPROCESS_H

#include <QByteArray>
#include <QFile>
#include <QDir>
#include <QPixmap>

class FileProcess
{
public:
    static bool saveFile(const QByteArray &byteArray, const QString &path, const QString &filename);

    static bool saveQPixmap(const QPixmap &pixmap, const QString &path, const QString &filename);

private:
    FileProcess();
};

#endif // FILEPROCESS_H
