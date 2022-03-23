/* Copyright (c) 2017-2022 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "xiodevice.h"

XIODevice::XIODevice(QObject *pParent) : QIODevice(pParent)
{

}

qint64 XIODevice::size() const
{
#ifdef QT_DEBUG
    qCritical("XIODevice::size");
#endif

    return 0;
}

bool XIODevice::isSequential() const
{
    return QIODevice::isSequential();
}

bool XIODevice::seek(qint64 nPos)
{
    return QIODevice::seek(nPos);
}

bool XIODevice::reset()
{
    return QIODevice::reset();
}

bool XIODevice::open(OpenMode mode)
{
    setOpenMode(mode);

    return true;
}

bool XIODevice::atEnd() const
{
    return (bytesAvailable()==0);
}

void XIODevice::close()
{
    setOpenMode(NotOpen);
}

qint64 XIODevice::pos() const
{
    return QIODevice::pos();
}

qint64 XIODevice::readData(char *pData, qint64 nMaxSize)
{
    Q_UNUSED(pData)
    Q_UNUSED(nMaxSize)

#ifdef QT_DEBUG
    qCritical("XIODevice::readData");
#endif

    return 0;
}

qint64 XIODevice::writeData(const char *pData, qint64 nMaxSize)
{
    Q_UNUSED(pData)
    Q_UNUSED(nMaxSize)

#ifdef QT_DEBUG
    qCritical("XIODevice::writeData");
#endif

    return 0;
}

void XIODevice::setErrorString(const QString &sString)
{
    QIODevice::setErrorString(sString);
}
