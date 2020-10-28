#include "response.h"
#include "common/logger/log.h"


const QString Response::keyValuePattern QStringLiteral("%1: %2\r\n");
const QString Response::statusLinePattern QStringLiteral("%1 %2 %3\r\n");
const QString Response::HTTPversion QStringLiteral("HTTP/1.1");

const QString Response::headerField::ContentType = QStringLiteral("Content-Type");
const QString Response::headerField::ContentLength = QStringLiteral("Content-Length");
const QString Response::headerField::Connection = QStringLiteral("Connection");
const QString Response::headerField::Server = QStringLiteral("Server");

    //Informational
const int Response::statusCode::Continue=100;
const int Response::statusCode::SwitchingProtocols=101;
//Successful
const int Response::statusCode::OK=200;
const int Response::statusCode::Created=201;
const int Response::statusCode::Accepted=202;
const int Response::statusCode::NonAuthoritativeInformation=203;
const int Response::statusCode::NoContent=204;
const int Response::statusCode::ResetContent=205;
const int Response::statusCode::PartialContent=206;
//Redirection;
const int Response::statusCode::MultipleChoices=300;
const int Response::statusCode::MovedPermanently=301;
const int Response::statusCode::Found=302;
const int Response::statusCode::SeeOther=303;
const int Response::statusCode::NotModified=304;
const int Response::statusCode::UseProxy=305;
const int Response::statusCode::TemporaryRedirect=307;
//Client Error
const int Response::statusCode::BadRequest=400;
const int Response::statusCode::Unauthorized=401;
const int Response::statusCode::PaymentRequired=402;
const int Response::statusCode::Forbidden=403;
const int Response::statusCode::NotFound=404;
const int Response::statusCode::MethodNotAllowed=405;
const int Response::statusCode::NotAcceptable=406;
const int Response::statusCode::ProxyAuthenticationRequired=407;
const int Response::statusCode::RequestTimeout=408;
const int Response::statusCode::Conflict=409;
const int Response::statusCode::Gone=410;
const int Response::statusCode::LengthRequired=411;
const int Response::statusCode::PreconditionFailed=412;
const int Response::statusCode::RequestEntityTooLarge=413;
const int Response::statusCode::RequestURItooLarge=414;
const int Response::statusCode::UnsupportedMediaType=415;
const int Response::statusCode::RequestedRangeNotSatisfiable=416;
const int Response::statusCode::ExpectationFailed=417;
//Server Error
const int Response::statusCode::InternalServerError=500;
const int Response::statusCode::NotImplemented=501;
const int Response::statusCode::BadGateway=502;
const int Response::statusCode::ServiceUnavailable=503;
const int Response::statusCode::GatewayTimeout=504;
const int Response::statusCode::HTTPversionNotSupported=505;


    const QMap<int, QString> Response::statuses {
        {101, QStringLiteral("Switching Protocols")},

        {Response::statusCode::OK, QStringLiteral("OK")},
        {Response::statusCode::Created, QStringLiteral("Created")},
        {202, QStringLiteral("Accepted")},
        {203, QStringLiteral("Non-Authoritative Information")},
        {204, QStringLiteral("No Content")},
        {205, QStringLiteral("Reset Content")},
        {206, QStringLiteral("Partial Content")},
        {300, QStringLiteral("Multiple Choices")},
        {301, QStringLiteral("Moved Permanently")},
        {302, QStringLiteral("Found")},
        {303, QStringLiteral("See Other")},
        {304, QStringLiteral("Not Modified")},
        {305, QStringLiteral("Use Proxy")},
        {307, QStringLiteral("Temporary Redirect")},

        {Response::statusCode::BadRequest, QStringLiteral("Bad Request")},
        {401, QStringLiteral("Unauthorized")},
        {402, QStringLiteral("Payment Required")},
        {403, QStringLiteral("Forbidden")},
        {Response::statusCode::NotFound, QStringLiteral("Not Found")},
        {Response::statusCode::MethodNotAllowed, QStringLiteral("Method Not Allowed")},
        {406, QStringLiteral("Not Acceptable")},
        {407, QStringLiteral("Proxy Authentication Required")},
        {408, QStringLiteral("Request Time-out")},
        {409, QStringLiteral("Conflict")},
        {410, QStringLiteral("Gone")},
        {411, QStringLiteral("Length Required")},
        {412, QStringLiteral("Precondition Failed")},
        {413, QStringLiteral("Request Entity Too Large")},
        {414, QStringLiteral("Request-URI Too Large")},
        {415, QStringLiteral("Unsupported Media Type")},
        {416, QStringLiteral("Requested range not satisfiable")},
        {417, QStringLiteral("Expectation Failed")},

        {Response::statusCode::InternalServerError, QStringLiteral("Internal Server Error")},
        {Response::statusCode::NotImplemented, QStringLiteral("Not Implemented")},
        {502, QStringLiteral("Bad Gateway")},
        {Response::statusCode::ServiceUnavailable, QStringLiteral("Service Unavailable")},
        {504, QStringLiteral("Gateway Time-out")},
        {505, QStringLiteral("HTTP Version not supported")},
        };

Response::Response()
{

}


//Response::Response(int s,const QByteArray& b)
//{
//    this->statusCode = s;
//    this->body =b;
//}

void Response::setStatus(int s)
{
    this->statusCode = s;
}


void Response::addBody(const QByteArray& b)
{
    this->body.append(b);
}

void Response::addHeaderField(const QString& k, const QString& v)
{
    if(!headerFields.contains(k))
    {
        headerFields.insert(k, v);
    }
    else
    {
        zError(QStringLiteral("headerField already exist: %1").arg(k));
    }
}

QByteArray Response::toByteArray()
{
    QByteArray b;

    b.append(statusLinePattern.arg(HTTPversion).arg(statusCode).arg(Response::statusPhrase(statusCode)).toUtf8());

    if(!body.isEmpty())
    {
        this->addHeaderField(Response::headerField::ContentLength, QString::number(body.length()));
    }

    for(auto i = headerFields.begin();i!=headerFields.end();i++)
    {
        b.append(keyValuePattern.arg(i.key(), i.value()).toUtf8());
    }

    b.append("\r\n");
    if(!body.isEmpty())
    {
        b.append(body);
    }
    return b;
}




QString Response::statusPhrase(int s)
{
    return statuses.value(s, QStringLiteral("Unknown"));
}

void Response::addBody(const ActionResult& a){
    addBody(a.content);
    addHeaderField(Response::headerField::ContentType, a.type+" charset=utf-8");
}


QString Response::getStatus()
{
    return QStringLiteral("%1: %2").arg(this->statusCode).arg(this->statusPhrase(this->statusCode));
}
