/*
 C++ RGPUI

 Created by Ralph-Gordon Paul on 08. Dec 2014.
-------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2014 Ralph-Gordon Paul. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-------------------------------------------------------------------------------
*/

#include "RGPUI.h"

#include <QApplication>
#include <QScreen>

#if defined(Q_OS_ANDROID)
#include <QAndroidJniObject>
#include <QtAndroid>
#endif

namespace rgp {

/*******************************************************************************
 *** Class: UI
 ******************************************************************************/

UI::UI(QObject *parent) :
    QObject(parent)
{
     QApplication *app = static_cast<QApplication *>(QApplication::instance());

    if ( app != nullptr ) {

#if defined(Q_OS_WIN) || defined(Q_OS_MAC)
        m_dpi = app->primaryScreen()->logicalDotsPerInch() *
                app->devicePixelRatio();
#elif defined(Q_OS_ANDROID)

        QAndroidJniObject qtActivity =
                QAndroidJniObject::callStaticObjectMethod(
                    "org/qtproject/qt5/android/QtNative",
                    "activity", "()Landroid/app/Activity;");
        QAndroidJniObject resources =
                qtActivity.callObjectMethod("getResources",
                                            "()Landroid/content/res/Resources;");
        QAndroidJniObject displayMetrics =
                resources.callObjectMethod("getDisplayMetrics",
                                           "()Landroid/util/DisplayMetrics;");
        int density = displayMetrics.getField<int>("densityDpi");
        m_dpi = static_cast<qreal>(density);
#else
        m_dpi = app->primaryScreen()->physicalDotsPerInch() *
                app->devicePixelRatio();
#endif
    }
}

// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------

// singleton type provider function (callback).
QObject * UI::provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    UI *instance = new rgp::UI();
    return instance;
}

// -----------------------------------------------------------------------------
// Accessors
// -----------------------------------------------------------------------------

qreal UI::dpi() const
{
    return m_dpi;
}

qreal UI::baseDpi() const
{
    return m_baseDpi;
}

void UI::setBaseDpi(qreal dpi)
{
    m_baseDpi = dpi;
    emit baseDpiChanged();
}

// -----------------------------------------------------------------------------
// pixel calculation
// -----------------------------------------------------------------------------

qreal UI::dp(qreal pixel)
{
    return pixel * m_dpi / m_baseDpi;
}

qreal UI::mm(qreal mm)
{
    return mm * m_dpi / 25.4;
}

qreal UI::cm(qreal cm)
{
    return cm * m_dpi / 2.54;
}

} // namespace rgp

