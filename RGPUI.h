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

#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QJSEngine>
#include <QtQml>

namespace rgp {

/**
  @brief UI Class
  @details UI Class to provide some system wide specifications like
  density independent pixel calculation.
*/
class UI : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal baseDpi READ baseDpi WRITE setBaseDpi
               NOTIFY baseDpiChanged)
public:
    explicit UI (QObject *parent = 0);

    /**
     @brief The density of the primary screen in dots per inch.
     */
    Q_INVOKABLE qreal dpi() const;

    /**
      @brief The base of the density indepentent pixel calculation.
      @details By default we assume a standard display to have 160 pixel per
               inch. The calculation of the independent pixel is based on that
               value. So a display with a dpi of 160 will have 1 real pixel per
               1 independent pixel and a display with a dpi of 320 will have 2
               real pixels per 1 independent pixel. You might change that value.
      @return The base dpi.
      @sa setBaseDpi(), dp()
    */
    qreal baseDpi() const;

    /**
      @brief Sets the base of the density indepentent pixel calculation.
      @details By default we assume a standard display to have 160 pixel per
               inch. The calculation of the independent pixel is based on that
               value. So a display with a dpi of 160 will have 1 real pixel per
               1 independent pixel and a display with a dpi of 320 will have 2
               real pixels per 1 independent pixel. Using this function you can
               change that value. One reason might be that you assumed a
               default by 96 dpi like Microsoft/Windows standard or 72 dpi like
               Apple/Macintosh standard.
      @sa baseDpi(), dp()
    */
    void setBaseDpi(qreal dpi);

    /**
      @brief Calculates density independent pixel.
      @details The calculation is based on the divergence from the baseDpi
               (by default: 160).
      @param pixel Pixels to be converted to density independent pixel
      @return density independent pixel
      @sa baseDpi()
      */
    Q_INVOKABLE qreal dp(qreal pixel);

    /**
      @brief Calculates the number of pixels for given millimeters.
      @param mm Number of millimeters to be converted.
      @return Number of pixels for the given amount of millimeters.
      */
    Q_INVOKABLE qreal mm(qreal mm);

    /**
      @brief Calculates the number of pixels for given centimeters.
      @param cm Number of centimeters to be converted.
      @return Number of pixels for the given amount of centimeters.
      */
    Q_INVOKABLE qreal cm(qreal cm);

    /**
      @brief Singleton type provider function (callback)
      @details The Singleton type provide function is used to register the UI
               class to QML. Use this provider as parameter in
               qmlRegisterSingletonType function. For example you can use this
               in your main.cpp:
               qmlRegisterSingletonType<rgp::UI>("com.rgpaul.RGPUI", 1, 0, "UI",
               rgp::UI::provider);
      @param engine
      @param scriptEngine
      @return the provider
    */
    static QObject *provider(QQmlEngine *engine, QJSEngine *scriptEngine);

signals:

    void baseDpiChanged();

public slots:

private:
    // base dpi - used to calculate the divergence from real dpi.
    // by default we assume that a standard display has 160 pixel per inch.
    qreal m_baseDpi { 160 };
    // default density has 160 dots per inch
    qreal m_dpi { 160 };
    // default scale factor: 1 independent pixel per pixel
    qreal m_contentScaleFactor { 1 };
};
}
