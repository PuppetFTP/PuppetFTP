#include "UnavailableProcessor.h"
#include "DefaultPageRenderer.h"
#include "Widget.h"

UnavailableProcessor::UnavailableProcessor() : AbstractRequestProcessor() {
}

UnavailableProcessor::~UnavailableProcessor() {
}

QStringList UnavailableProcessor::getRequiredCrendentials() const {
    QStringList list;
    return list;
}

void UnavailableProcessor::process(HTTPRequest& request) {
}

QByteArray UnavailableProcessor::render() const {
    UI::DefaultPageRenderer page;


    page.setTitle("PuppetFTP - Unavailable page");

    UI::Container* divContent = new UI::Container();
    divContent->setId("unavailable");
    divContent->addWidget(new UI::Title("This page is currently unavailable in this version product."));
    divContent->addWidget(new UI::Image("/images/under_construction.jpg"));

    page.body()->addWidget(divContent);
    return page.render();
}
