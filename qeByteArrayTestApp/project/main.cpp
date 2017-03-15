/*  main.cpp
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
 * Simple application to read and write to a QEByteArray.
 *
 * this application takes a single parameter - an EPICS Variable Name. Typically for a waveform record.
 *
 * A simple class - arraywriter - is instantiated that creates a QEByteArray object, connects
 * to its signals, then regularly writes to it.
 *
 * Like all QE EPICS data types such as QEInteger, QEString, QEFloating, etc, QEByteArray will
 * present any EPICS data as a QByteArray no matter what the underlying EPICS data type, and
 * write a QByteArray no matter what the underlying EPICS data type.
 * Typically, however, a QEByteArray would be used to access raw data from an EPICS waveform or
 * string record.
 */

#include <QtCore/QCoreApplication>
#include <arraywriter.h>

int main(int argc, char *argv[])
{
    // Initialise
    QCoreApplication a(argc, argv);
    QTextStream* outStream = new QTextStream( stdout );

    // check a PV is available
    if( argc != 2 )
    {
        *outStream << QString( "One parameter required: EPICS Variable Name\n" );
        outStream->flush();
        return 0;
    }

    // Instantiate an array writer class which will create a QEByteArray object and exersize it.
    arrayWriter* aw = new arrayWriter( argv[1], outStream );

    // Do stuff
    return a.exec();

    // Cleanup
    delete aw;
}
