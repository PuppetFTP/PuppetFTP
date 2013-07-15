#include "UnavailableProcessor.h"
#include "DefaultPageRenderer.h"
#include "Widget.h"
#include "Translate.h"

UnavailableProcessor::UnavailableProcessor() : AbstractRequestProcessor() {
}

UnavailableProcessor::~UnavailableProcessor() {
}

void UnavailableProcessor::process(HTTPRequest& request) {
}

QByteArray UnavailableProcessor::render() const {
    UI::DefaultPageRenderer page;

    Translate::instance()->group("unavailable");

    page.setTitle("PuppetFTP - "+Translate::instance()->tr("title"));

    UI::Container* divContent = new UI::Container();
    divContent->setId("unavailable");
    divContent->addWidget(new UI::Title(Translate::instance()->tr("text")));
    divContent->addWidget(new UI::Image("/img/under_construction.jpg"));

    page.body()->addWidget(divContent);
    return page.render();
}
