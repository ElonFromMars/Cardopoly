#pragma once

#include <any>
#include <atomic>
#include <functional>
#include <mutex>
#include <shared_mutex>
#include <system_error>
#include <typeindex>
#include <unordered_map>
#include <utility>

#include "Cardopoly/EventBus/Details/function_traits.hpp"
#include "Cardopoly/EventBus/HandlerRegistration.h"

class EventBus
{
	using mutexType = std::shared_mutex;
	mutable mutexType _registrationMutex;
	std::unordered_multimap<std::type_index, HandlerRegistration> _handlerRegistrations;
	
public:
	EventBus() = default;

	template <typename EventType, typename ClassType, typename MemberFunction>
	void Subscribe(ClassType* target, MemberFunction&& function) noexcept
	{
		using traits = detail::function_traits<MemberFunction>;
		static_assert(std::is_same_v<ClassType, std::decay_t<typename traits::owner_type>>,
		              "Member function pointer must match instance type.");

		const auto typeIdx = std::type_index(typeid(EventType));

		if constexpr (traits::arity == 0)
		{
			auto handler = HandlerRegistration(static_cast<const void*>(target),
				[target, function](auto)
					{
						(target->*function)();
					}
				);
				
			_handlerRegistrations.emplace(typeIdx, std::move(handler));
		}
		else
		{
			auto handler = HandlerRegistration(static_cast<const void*>(target),
					[target, function](auto value)
					{
						(target->*function)(std::any_cast<EventType>(value));
					}
				);
				
			_handlerRegistrations.emplace(typeIdx, std::move(handler));
		}
	}

	template <typename EventType, typename = std::enable_if_t<!std::is_pointer_v<EventType>>>
	void FireEvent(EventType&& evt) noexcept
	{
		for (auto [beginEvtId, endEvtId] =
					 _handlerRegistrations.equal_range(std::type_index(typeid(EventType)));
				 beginEvtId != endEvtId; ++beginEvtId)
		{
			beginEvtId->second.Handler(std::forward<EventType>(evt));
		}
	}

	template <typename EventType, typename ClassType>
	bool Unsubscribe(ClassType* target) noexcept
	{
		auto result = false;
		auto targetPtr = static_cast<const void*>(target);
		for (auto [beginEvtId, endEvtId] =
					 _handlerRegistrations.equal_range(std::type_index(typeid(EventType)));
				 beginEvtId != endEvtId; ++beginEvtId)
		{
			if (beginEvtId->second.Target == targetPtr)
			{
				_handlerRegistrations.erase(beginEvtId);
				result = true;
				break;
			}
		}
		
		return result;
	}

	void UnsubscribeAll() noexcept
	{
		_handlerRegistrations.clear();
	}

	[[nodiscard]] std::size_t GetListenersCount() const noexcept
	{
		std::size_t count{};
		return count = _handlerRegistrations.size();;
	}
};
