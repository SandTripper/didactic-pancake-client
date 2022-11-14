#include "FileProcess.h"

bool FileProcess::saveFile(const QByteArray &byteArray, const QString &path, const QString &filename)
{
    QDir dir(path);
    if (!dir.exists())
    {
        bool ismkdir = dir.mkpath(path);
        if (!ismkdir)
            return false;
    }
    QFile file(path + "/" + filename);
    if (!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    file.write(byteArray);
    file.close();
    return true;
}

bool FileProcess::saveQPixmap(const QPixmap &pixmap, const QString &path, const QString &filename)
{
    QDir dir(path);
    if (!dir.exists())
    {
        bool ismkdir = dir.mkpath(path);
        if (!ismkdir)
            return false;
    }

    pixmap.save(path + "/" + filename);
    return true;
}

FileProcess::FileProcess()
{
}
