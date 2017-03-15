#ifndef ARRAYWRITER_H
#define ARRAYWRITER_H

#include <QEByteArray.h>
#include <QTextStream>
//#include <UserMessage.h>

class arrayWriter : public QObject//, public UserMessage
{
    Q_OBJECT

public:
    arrayWriter( QString pv, QTextStream* outStreamIn ); // Construction
    ~arrayWriter();// Destruction

private:
    QEByteArray* ba;    // epicsqt Byte Array sink/source

    UserMessage messages;
    QTextStream* outStream; // Logging stream

    void timerEvent( QTimerEvent *event );// Timer event to do regular writes
    void printByteArray( const QByteArray& array ); // Common log of byte array data used when reading and writing

    unsigned long elementSize;  // EPCIS record date element size

private slots:
    void connectionChanged( QCaConnectionInfo& connectionInfo, const unsigned int& );// Log data updates
    void log( const QByteArray& data, unsigned long len, QCaAlarmInfo&, QCaDateTime& timeStamp, const unsigned int& );// Log connection changes
};

#endif // ARRAYWRITER_H
