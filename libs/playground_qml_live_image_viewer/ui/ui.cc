// Copyright (C) 2024 twyleg
#include "ui.h"

#include <QQmlContext>

#include <boost/optional.hpp>
#include <fmt/core.h>

#include <iostream>

namespace playground_qml_live_image_viewer::ui {

UI::UI(int argc, char **argv) :
	QQuickImageProvider(QQuickImageProvider::Pixmap),
    mArgc(argc),
    mArgv(argv),
	mApplication(mArgc, mArgv)
{}

UI::~UI() {}

QPixmap UI::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {
   return mImageModel.getImage();
}

int UI::run() {

	mEngine.rootContext()->setContextProperty("imageModel", &mImageModel);
	mEngine.rootContext()->setContextProperty("parameterModel", &mParameterModel);
	mEngine.addImageProvider("stream", this);

    mEngine.load(":/qml/main_window.qml");

    return mApplication.exec();
}

}
