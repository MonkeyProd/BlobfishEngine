//
// Created by plasm on 21.07.2022.
//

#ifndef COMPOUND_CUSTOMEVENT_H
#define COMPOUND_CUSTOMEVENT_H

#include <ostream>
#include "Event.h"

namespace bf {
    class CustomEvent : public Event {
    public:
        DECLARE_EVENT_CLASS(EventType::CustomEvent)

        virtual std::string ToString() const override {
            return "CustomEvent";
        }
    };

//    class ExampleCustomEvent : public CustomEvent {
//    public:
//        ExampleCustomEvent(int mData) : m_data(mData) { BF_LOG_DEBUG("My custom event created"); }
//
//        const char *GetName() const override {
//            return "My custom event";
//        }
//
//        int GetCategoryFlags() const override {
//            return EventCategory::EMouse;
//        }
//
//        EventType GetEventType() const override {
//            return EventType::CustomEvent;
//        }
//
//        std::string ToString() const override {
//            return std::string(GetName()) + "data: " + std::to_string(m_data);
//        }
//
//    private:
//        int m_data;
//    };
}
#endif //COMPOUND_CUSTOMEVENT_H
