/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#ifndef HTTPSENDER_H
#define HTTPSENDER_H

#include <QObject>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QNetworkRequest>
#include <QUrl>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QThread>

class HttpSender : public QThread
{
    Q_OBJECT
public:
    enum Status
    {
        FILE_ERROR,
        NO_ERROR
    };

    HttpSender();

    void run() Q_DECL_OVERRIDE
    {
        Status status = this->sendFile();
        if(status == Status::NO_ERROR)
            this->exec();

        emit statusChanged(status);
    }

    QNetworkReply * reply;
    QNetworkAccessManager * manager;
    QHttpMultiPart * container;
    QFile * file;

public slots:
    /** Upload settings setters **/
    void setHost(QString const &host, int port)
    {
        url.setUrl(host);
        url.setPort(port);
    }

    void setFile(QString const &pathToFile)
    {
        this->pathToFile = pathToFile;
    }

    void setPasteSettings(QByteArray const &lang, QString const &langHR)
    {
        this->lang = lang;
        this->langHR = langHR;
    }

    void setUsername(QString const &username)
    {
        this->username = username;
    }

    void setPrivateKey(QString const &privateKey)
    {
        this->privateKey = privateKey;
    }

    void setUplimgVersion(QString const &uplimgVersion)
    {
        this->uplimgVersion = uplimgVersion;
    }

    QString getResponse()
    {
        return QString(reply->readAll());
    }

signals:
    void finished();
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void error(QNetworkReply::NetworkError);
    void statusChanged(Status);


protected:
    Status sendFile();

    QUrl url;
    QString pathToFile;
    QString username;
    QString privateKey;
    QString uplimgVersion;
    /** Paste specific **/
    QByteArray lang;
    QString langHR;
};

#endif // HTTPSENDER_H
