/*
    Copyright (C) 2016 Volker Krause <vkrause@kde.org>

    Permission is hereby granted, free of charge, to any person obtaining
    a copy of this software and associated documentation files (the
    "Software"), to deal in the Software without restriction, including
    without limitation the rights to use, copy, modify, merge, publish,
    distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so, subject to
    the following conditions:

    The above copyright notice and this permission notice shall be included
    in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
    IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
    SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef KUSERFEEDBACK_APPLICATIONVERSIONSOURCE_H
#define KUSERFEEDBACK_APPLICATIONVERSIONSOURCE_H

#include "kuserfeedbackcore_export.h"
#include "abstractdatasource.h"

namespace KUserFeedback {

/*! Data source for the application version.
 *  The application version is retrieved via QCoreApplication::applicationVersion.
 *
 *  The default telemetry mode for this source is Provider::BasicSystemInformation.
 */
class KUSERFEEDBACKCORE_EXPORT ApplicationVersionSource : public AbstractDataSource
{
    Q_DECLARE_TR_FUNCTIONS(KUserFeedback::ApplicationVersionSource)
public:
    /*! Create a new application version source. */
    ApplicationVersionSource();

    QString name() const override;
    QString description() const override;

    QVariant data() override;
};

}

#endif // KUSERFEEDBACK_APPLICATIONVERSIONSOURCE_H
