/*
 * ResourceProcessor.cpp
 *
 *  Created on: 12 déc. 2012
 *      Author: laplace
 */

#include <QFileInfo>
#include "ResourceProcessor.h"

ResourceProcessor::ResourceProcessor() {
    _headerParameters["Content-Transfer-Encoding"] = "binary";
}

ResourceProcessor::~ResourceProcessor() {
}

QString ResourceProcessor::getContentType() const {
    return _contentType;
}

bool ResourceProcessor::hasAdditionalHeaderParameters() const {
    return true;
}

QHash<QString, QString> ResourceProcessor::getAdditionalHeaderParameters() const {
    return _headerParameters;
}

QStringList ResourceProcessor::getRequiredCredentials() const {
    return QStringList();
}
UI::Notify* ResourceProcessor::getNotify() const {
    return NULL;
}

void ResourceProcessor::process(HTTPRequest& request) {
    _resource.setFileName("./web/" + request.getRequestedURI());
    // Content type
    QFileInfo fileinfo(_resource.fileName());
    if (fileinfo.suffix() == "png") {
        _contentType = "image/png";
    }
    else if (fileinfo.suffix() == "jpg" || fileinfo.completeSuffix() == "jpeg") {
        _contentType = "image/jpeg";
    }
    else if (fileinfo.suffix() == "js") {
        _contentType = "application/javascript";
    }
    else if (fileinfo.suffix() == "css") {
        _contentType = "text/css";
    }
    else {
        _contentType = "application/octet-stream";
    }
    // Content
    if (_resource.open(QIODevice::ReadOnly) == true) {
        _bytes.append(_resource.read(_resource.size()));
        _resource.close();
    }
}

QByteArray  ResourceProcessor::render() const {
    return _bytes;
}

