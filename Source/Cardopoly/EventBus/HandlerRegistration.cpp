#include "HandlerRegistration.h"

HandlerRegistration::HandlerRegistration(const void* target, std::function<void(std::any)> handler)
	: Target(target), Handler(handler)
{
}

HandlerRegistration::HandlerRegistration(HandlerRegistration&& other) noexcept
	: Target(other.Target),
	  Handler(other.Handler)
{
}

HandlerRegistration& HandlerRegistration::operator=(HandlerRegistration&& other) noexcept
{
	Handler = std::move(other.Handler);
	Target = std::exchange(other.Target, nullptr);
	
	return *this;
}