#pragma once

#include <any>
#include <functional>

class HandlerRegistration
{
public:
	const void* Target;
	std::function<void(std::any)> Handler;
	
	HandlerRegistration(const void* target, std::function<void(std::any)> handler);
	HandlerRegistration(HandlerRegistration&& other) noexcept;
	
	HandlerRegistration(const HandlerRegistration& other) = delete;

	HandlerRegistration& operator=(HandlerRegistration&& other) noexcept;

	HandlerRegistration& operator=(const HandlerRegistration& other) = delete;
};
