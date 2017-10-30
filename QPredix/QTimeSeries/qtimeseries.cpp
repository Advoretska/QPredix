#include "qtimeseries.h"
#include "qtimeseriesrequests.h"
#include "qtimeseriesparser.h"

#include "../QUaa/quaa.h"

#include <QDebug>

QTimeSeries::QTimeSeries(QUaa *uaa, QObject *parent) : QObject(parent),
    mUaa{uaa},
    mRequest{nullptr}
{
    if (uaa != nullptr) {
        mRequest = new QTimeSeriesRequests(mUaa);
        connect(mRequest, SIGNAL(tagsReceived(QByteArray)), this, SLOT(tagsReceived(QByteArray)));
        connect(mRequest, SIGNAL(latestDatapointsReceived(QByteArray)), this, SIGNAL(latestDatapoints(QByteArray)));
        connect(mRequest, SIGNAL(customRequestResponseReceived(QByteArray)), this, SIGNAL(customRequestResponse(QByteArray)));
        connect(mRequest, SIGNAL(limitedDatapointsReceived(QByteArray)), this, SIGNAL(limitedDatapoints(QByteArray)));
        connect(mRequest, SIGNAL(fromToDatapointsReceived(QByteArray)), this, SIGNAL(fromToDatapoints(QByteArray)));
    }
}

QTimeSeries::~QTimeSeries()
{
    if (mRequest != nullptr) {
        delete mRequest;
    }
}

void QTimeSeries::sendCustomRequest(QString req)
{
    if (mRequest != nullptr) {
        mRequest->sendCustomRequest(req, mZoneID);
    }
}

void QTimeSeries::getTags()
{
    if (mRequest != nullptr) {
        mRequest->getAllTags(mZoneID);
    }
}

void QTimeSeries::getLatestDatapoints(QStringList tags)
{
    qDebug() << __FUNCTION__;
    if (mRequest != nullptr) {
        mRequest->getLatestDatapoints(tags, mZoneID);
    }
}

void QTimeSeries::getLimitedDatapoints(QStringList tags, int count)
{
    if (mRequest != nullptr) {
        mRequest->getLimitedDatapoints(tags, count, mZoneID);
    }
}

void QTimeSeries::getFromToDatapoints(QStringList tags, QString from, QString to)
{
    if (mRequest != nullptr) {
        mRequest->getFromToDatapoints(tags, from, to, mZoneID);
    }
}

void QTimeSeries::sendData(QString tagName, QString data, QString quality, QString attributes)
{
    if (mRequest != nullptr) {
        mRequest->openSocket(mZoneID);
        mRequest->sendData(tagName, data, quality, attributes);
    }
}

QString QTimeSeries::zoneID() const
{
    return mZoneID;
}

void QTimeSeries::setZoneID(const QString &zoneID)
{
    mZoneID = zoneID;
}

void QTimeSeries::tagsReceived(QByteArray tags)
{
    QStringList lList = QTimeSeriesParser::parseTagsResponse(tags);

    emit tagsList(lList);
}
