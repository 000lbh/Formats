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
#ifndef XDATACONVERTOR_H
#define XDATACONVERTOR_H

#include "xbinary.h"

class XDataConvertor : public QObject {
    Q_OBJECT

public:
    enum CMETHOD {
        CMETHOD_UNKNOWN = 0,
        CMETHOD_XOR_BYTE,
        CMETHOD_XOR_WORD,
        CMETHOD_XOR_DWORD,
        CMETHOD_XOR_QWORD
    };

    struct OPTIONS{
        QVariant varKey;
    };

    explicit XDataConvertor(QObject *pParent = nullptr);
    void setData(QIODevice *pDeviceIn, QIODevice *pDeviceOut, CMETHOD method, const OPTIONS &options, XBinary::PDSTRUCT *pPdStruct);

public slots:
    void process();

signals:
    void errorMessage(const QString &sText);
    void completed(qint64 nElapsed);

private:
    QIODevice *g_pDeviceIn;
    QIODevice *g_pDeviceOut;
    CMETHOD g_method;
    OPTIONS g_options;
    XBinary::PDSTRUCT *g_pPdStruct;
};

#endif  // XDATACONVERTOR_H
