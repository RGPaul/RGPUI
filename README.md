# RGP_UI
RGP_UI is a Qt Helper Class for common QML needs.
The Class itself will be registered to QML as singleton.

Features:
* Density independent pixel

### QML:
```QML
import QtQuick 2.4
import QtQuick.Window 2.2
import com.rgpaul.RGPUI 1.0

ApplicationWindow {
  width: UI.dp(800)
  height: UI.dp(600)
  
  // creates a 1x1cm rectangle
  Rectangle {
    width: UI.cm(1) height: UI.cm(1)
    anchors.centerIn: parent
    color: "green"
  }
}
```

### To register the singleton to your QML:
```c++
#include "RGP_UI/RGP_UI.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;
    
    qmlRegisterSingletonType<rgp::UI>("com.rgpaul.RGPUI", 1, 0, "UI", rgp::UI::provider);

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    return app.exec();
}
```

### LICENSE
```
-------------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2015 Ralph-Gordon Paul. All rights reserved.

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
```
