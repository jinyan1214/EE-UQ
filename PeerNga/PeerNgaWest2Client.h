#ifndef PEERNGAWEST2CLIENT_H
#define PEERNGAWEST2CLIENT_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkCookieJar>
#include <QNetworkCookie>

class PeerNgaWest2Client : public QObject
{
    Q_OBJECT
public:
    explicit PeerNgaWest2Client(QObject *parent = nullptr);
    bool loggedIn();
    void signIn(QString username, QString password);
    void selectRecords(double sds, double sd1, double tl, int nRecords, QVariant magnitudeRange, QVariant distanceRange, QVariant vs30Range);

signals:
    void loginFinished(bool result);
    void recordsDownloaded(QString recordsPath);
    void statusUpdated(QString status);

public slots:

private:
    QNetworkAccessManager networkManager;

    QNetworkReply* signInPageReply;
    QNetworkReply* signInReply;
    QNetworkReply* getSpectraReply;
    QNetworkReply* postSpectraReply;
    QNetworkReply* postSearchReply;
    QNetworkReply* getRecordsReply;
    QNetworkReply* downloadRecordsReply;

    QString authenticityToken;
    QString username;
    QString password;
    int nRecords;
    bool isLoggedIn;

    QVariant magnitudeRange;
    QVariant distanceRange;
    QVariant vs30Range;

    //Data for retry on failure
    int retries;
    QList<QNetworkCookie> signInCookies;
    QNetworkRequest postSpectraRequest;
    QUrlQuery postSpectraParameters;
    QNetworkRequest peerSignInRequest;
    QUrlQuery signInParameters;

    void setupConnection();
    void processNetworkReply(QNetworkReply *reply);

    void processSignInPageReply();
    void processSignInReply();
    void processPostSpectrumReply();
    void processPostSearchReply();
    void processGetRecordsReply();
    void processDownloadRecordsReply();
    void retryPostSpectra();
    void retrySignIn();


};

#endif // PEERNGAWEST2CLIENT_H
