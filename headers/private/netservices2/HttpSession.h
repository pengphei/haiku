/*
 * Copyright 2022 Haiku Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */

#ifndef _B_HTTP_SESSION_H_
#define _B_HTTP_SESSION_H_

#include <memory>

#include <Messenger.h>

class BUrl;


namespace BPrivate {

namespace Network {

class BHttpRequest;
class BHttpResult;


class BHttpSession {
public:
	// Constructors & Destructor
							BHttpSession();
							BHttpSession(const BHttpSession&) noexcept;
							BHttpSession(BHttpSession&&) noexcept = delete;
							~BHttpSession() noexcept;

	// Assignment operators
	BHttpSession&			operator=(const BHttpSession&) noexcept;
	BHttpSession&			operator=(BHttpSession&&) noexcept = delete;


	// Requests
	BHttpResult				Execute(BHttpRequest&& request,
								std::unique_ptr<BDataIO> target = nullptr,
								BMessenger observer = BMessenger());

private:
	class Request;
	class Impl;
	std::shared_ptr<Impl>	fImpl;
};


}

}

#endif // _B_HTTP_REQUEST_H_