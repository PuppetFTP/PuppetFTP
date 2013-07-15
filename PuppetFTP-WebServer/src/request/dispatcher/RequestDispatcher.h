/*
 * RequestDispatcher.h
 *
 *  Created on: 3 oct. 2012
 *      Author: laplace
 */

#ifndef REQUESTDISPATCHER_H_
#define REQUESTDISPATCHER_H_

#include <QString>
#include "HTTPRequest.h"
#include "HTTPResponse.h"
#include "Session.h"
#include "IRequestProcessor.h"
#include "Route.h"


class RequestDispatcher {
private:
    static RequestDispatcher*         _instance;
	RequestDispatcher();
	virtual ~RequestDispatcher();

    bool canAccessToRoute(Routing::Route* route, const Session& session, const HTTPRequest& request) const;

public:
	static RequestDispatcher* instance();
	static void               destroy();

	bool                      configure();
	HTTPResponse              dispatch(HTTPRequest& request);
};

#endif /* RESQUESTDISPATCHER_H_ */
