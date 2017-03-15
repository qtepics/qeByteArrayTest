/*  arraywritter.cpp
 *
 *  This file is part of the EPICS QT Framework, initially developed at the Australian Synchrotron.
 *
 *  The EPICS QT Framework is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  The EPICS QT Framework is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with the EPICS QT Framework.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Copyright (c) 2015 Australian Synchrotron
 *
 *  Author:
 *    Andrew Rhyder
 *  Contact details:
 *    andrew.rhyder@synchrotron.org.au
 */

/*
 * Simple class to read and write to a QEByteArray.
 *
 * Like all QE EPICS data types such as QEInteger, QEString, QEFloating, etc, QEByteArray will
 * present any EPICS data as a QByteArray no matter what the underlying EPICS data type, and
 * write a QByteArray no matter what the underlying EPICS data type.
 * Typically, however, a QEByteArray would be used to access raw data from an EPICS waveform or
 * string record.
 */

#include <QTimerEvent>
#include "arraywriter.h"

// QEByteArray manager construction
arrayWriter::arrayWriter( QString pv, QTextStream* outStreamIn )
{
    // Note stream for logging
    outStream = outStreamIn;

    // Initially we don't know how large each element in the EPICS record is
    elementSize = 0;

    // Create a QEByteArray object to write to and read from
    ba = new QEByteArray( pv, this, 0 );

    // Connect to the QEByteArray to recieve connection and data signals
    QObject::connect( ba, SIGNAL( byteArrayChanged( const QByteArray&, unsigned long, QCaAlarmInfo&, QCaDateTime&, const unsigned int& ) ),
                      this, SLOT( log( const QByteArray&, unsigned long, QCaAlarmInfo&, QCaDateTime&, const unsigned int& ) ) );

    QObject::connect( ba, SIGNAL( byteArrayConnectionChanged( QCaConnectionInfo&, const unsigned int& ) ),
                      this, SLOT( connectionChanged( QCaConnectionInfo&, const unsigned int& ) ) );

    // Start a subscription
    ba->subscribe();

    // Kick of writing every second
    startTimer( 1000 );
}

// QEByteArray manager destruction
arrayWriter::~arrayWriter()
{
    delete ba;
}

// Log data updates
void arrayWriter::log( const QByteArray& data, unsigned long elementSizeIn, QCaAlarmInfo&, QCaDateTime& timeStamp, const unsigned int& )
{
    // Note the EPICS data element size
    elementSize = elementSizeIn;

    // Log Timestamp and byte array data
    *outStream << QString( "%1: ").arg( timeStamp.text() );
    printByteArray( data );

    // Line termination
    *outStream << QString( "\n" );

    // Sync output
    outStream->flush();
}

// Log connection changes
void arrayWriter::connectionChanged( QCaConnectionInfo& connectionInfo, const unsigned int& )
{
    // Log all channel and link information
    *outStream << QString( "%1: %2  %3\n").arg( QTime::currentTime().toString() )
                                          .arg( connectionInfo.isChannelConnected()?"Channel connected":"Channel not connected" )
                                          .arg( connectionInfo.isLinkUp()?"Link up":"Link not up" );

    // Sync output
    outStream->flush();
}

// Timer event to do regular writes
void arrayWriter::timerEvent(QTimerEvent* /*event*/ )
 {
    // Do nothing until we know what the EPICS element size is.
    // A significant point of the QEByteArray class is that is reads and writes raw data without
    // regard to type or element size, but this will allow us to generate an appropriately sized chunk of data
    if( !elementSize )
        return;

    // Determine the amount of ddata to create
    int dataSize = ba->getElementCount() * elementSize;

    // Build a byte array of incrementing byte values, starting one higher (up to 100) each time this function is called
    static int next = 0;
    QByteArray data;
    for( int i = 0; i < dataSize; i++ )
    {
        data.append( next + i );
    }
    next = (next>=100)?0:(next+1);

    // Log what is to be written
    *outStream << "Writing: ";
    printByteArray( data );
    outStream->flush();

    // Write it
    ba->writeByteArray( data );
}

// Common log of byte array data used when reading and writing
void arrayWriter::printByteArray( const QByteArray& array )
{
    int len = array.length();
    len = (len>2000)?2000:len;
    for( int i = 0; i < len; i++)
    {
        *outStream << QString( "%1 ").arg( (int)(array.at(i)));
    }
}
