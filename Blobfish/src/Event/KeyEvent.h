//
// Created by plasm on 14.07.2022.
//

#ifndef COMPOUND_KEYEVENT_H
#define COMPOUND_KEYEVENT_H

#include "Event.h"
#include "../Core/BlobPCH.h"

namespace bf {
    class KeyPressedEvent : public Event {
        int m_category = EventCategory::EInput | EventCategory::EKeyboard;
        int m_keycode;
        bool m_isRepeat;
    public:
        KeyPressedEvent(int p_keycode, bool p_isRepeat) : m_keycode(p_keycode), m_isRepeat(p_isRepeat) {}

        DECLARE_EVENT_CLASS(EventType::KeyPressed)

        std::string ToString() const override {
            std::string result =
                    "KeyPressedEvent: " + std::to_string(m_keycode) + " (repeat = " + std::to_string(m_isRepeat) + ")";
            return result;
        }

        int getKeycode()const{
            return m_keycode;
        }

        bool getIsRepeat() const {
            return m_isRepeat;
        }
    };


    class KeyReleasedEvent : public Event {
        int m_category = EventCategory::EInput | EventCategory::EKeyboard;
        int m_keycode;
    public:
        KeyReleasedEvent(int p_keycode) : m_keycode(p_keycode) {}

        DECLARE_EVENT_CLASS(EventType::KeyReleased)

        std::string ToString() const override {
            std::string result = "KeyReleasedEvent: " + std::to_string(m_keycode) + ")";
            return result;
        }
    };
}

#endif //COMPOUND_KEYEVENT_H
