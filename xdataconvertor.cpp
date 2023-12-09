/* Copyright (c) 2020-2023 hors<horsicq@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "xdataconvertor.h"

XDataConvertor::XDataConvertor(QObject *pParent) : QObject(pParent)
{
    g_options = {};
}

void XDataConvertor::setData(QIODevice *pDeviceIn, QIODevice *pDeviceOut, CMETHOD method, const OPTIONS &options, XBinary::PDSTRUCT *pPdStruct)
{
    this->g_pDeviceIn = pDeviceIn;
    this->g_pDeviceOut = pDeviceOut;
    this->g_method = method;
    this->g_options = options;
    this->g_pPdStruct = pPdStruct;
}

void XDataConvertor::process()
{
    XBinary::PDSTRUCT pdStructEmpty = XBinary::createPdStruct();
    XBinary::PDSTRUCT *pPdStruct = g_pPdStruct;

    if (!pPdStruct) {
        pPdStruct = &pdStructEmpty;
    }

    QElapsedTimer scanTimer;
    scanTimer.start();

    qint32 _nFreeIndex = XBinary::getFreeIndex(pPdStruct);
    XBinary::setPdStructInit(pPdStruct, _nFreeIndex, 0);

    qint64 nOutSize = 0;
    qint64 nBufferSize = 0;
    qint64 nInSize = g_pDeviceIn->size();

    if (g_method == CMETHOD_XOR_BYTE) {
        nOutSize = nInSize;
        nBufferSize = 0x1000;
    }

    char *pBuffer = new char[nBufferSize];

    if(XBinary::resize(g_pDeviceOut, nOutSize)) {
        for (qint32 i = 0; i < nInSize; ) {
            qint64 _nBufferSize = qMin(nBufferSize, nInSize - i);

            g_pDeviceIn->seek(i);
            g_pDeviceOut->seek(i);

            if (g_pDeviceIn->read(pBuffer, _nBufferSize) != _nBufferSize) {
                pPdStruct->sErrorString = tr("Read error");
                break;
            }

            if (g_method == CMETHOD_XOR_BYTE) {
                for (qint32 j = 0; j < _nBufferSize; j++) {
                    pBuffer[j] = pBuffer[j] ^ (quint8)g_options.varKey.toUInt();
                }
            }

            if (g_pDeviceOut->write(pBuffer, _nBufferSize) != _nBufferSize) {
                pPdStruct->sErrorString = tr("Write error");
                break;
            }

            i +=  _nBufferSize;

            if (_nBufferSize == 0) {
                pPdStruct->sErrorString = tr("Read error");
                break;
            }
        }
    } else {
        pPdStruct->sErrorString = tr("Cannot resize");
    }

    delete [] pBuffer;
    // TODO

    XBinary::setPdStructFinished(pPdStruct, _nFreeIndex);

    emit completed(scanTimer.elapsed());
}