
/*
==========================================
  Copyright (c) 2016-2018 Dynamic_Static
    Patrick Purcell
      Licensed under the MIT license
    http://opensource.org/licenses/MIT
==========================================
*/

#include "Dynamic_Static/Core/Events/Event.hpp"
#include "Dynamic_Static/Core/Random.hpp"

#include "catch.hpp"

#include <vector>

namespace Dynamic_Static {
namespace Tests {

    static constexpr int TestCount { 16 };

    class Publisher final
    {
    public:
        Event<Publisher, const Publisher&> on_event;

        void fire_event() const
        {
            on_event(*this);
        }
    };

    class Listener final
    {
    private:
        int mInvocationCount { };
        Delegate<const Publisher&> mOnPublisherEvent;

    public:
        int get_invocation_count() const
        {
            return mInvocationCount;
        }

        size_t get_subscription_count() const
        {
            return mOnPublisherEvent.get_subscriptions().size();
        }

        void subscribe(Publisher& publisher)
        {
            publisher.on_event += mOnPublisherEvent;
            bind_delegate();
        }

    private:
        void on_publisher_event(const Publisher& publisher)
        {
            ++mInvocationCount;
        }

        void bind_delegate()
        {
            using namespace std::placeholders;
            mOnPublisherEvent = std::bind(&Listener::on_publisher_event, this, _1);
        }
    };

    static void activate_publishers(std::vector<Publisher>& publishers)
    {
        for (const auto& publisher : publishers) {
            publisher.fire_event();
        }
    }

    static bool validate_invocation(const std::vector<Listener>& listeners)
    {
        bool allListenersInvoked = true;
        for (const auto& listener : listeners) {
            if (listener.get_invocation_count() != listener.get_subscription_count()) {
                allListenersInvoked = false;
                break;
            }
        }
        return allListenersInvoked;
    }

    static void create_randomized_subscriptions(
        std::vector<Publisher>& publishers,
        std::vector<Listener>& listeners
    )
    {
        dst::RandomNumberGenerator rng;
        for (auto& publisher : publishers) {
            for (auto& listener : listeners) {
                if (rng.probability(0.5f)) {
                    listener.subscribe(publisher);
                }
            }
        }
    }

    TEST_CASE("Delegates can be assigned and called through Events", "[Event]")
    {
        std::vector<Publisher> publishers(TestCount);
        std::vector<Listener> listeners(TestCount);
        create_randomized_subscriptions(publishers, listeners);
        activate_publishers(publishers);
        REQUIRE(validate_invocation(listeners));
    }

    TEST_CASE("Events are moveable", "[Event]")
    {
        std::vector<Publisher> publishersMoveFrom(TestCount);
        std::vector<Listener> listenersMoveFrom(TestCount);
        create_randomized_subscriptions(publishersMoveFrom, listenersMoveFrom);
        std::vector<Publisher> publishersMoveTo;
        std::vector<Listener> listenersMoveTo;
        for (int i = 0; i < TestCount; ++i) {
            publishersMoveTo.push_back(std::move(publishersMoveFrom[i]));
            listenersMoveTo.push_back(std::move(listenersMoveFrom[i]));
        }
        activate_publishers(publishersMoveTo);
        REQUIRE(validate_invocation(listenersMoveTo));
    }

} // namespace Tests
} // namespace Dynamic_Static
