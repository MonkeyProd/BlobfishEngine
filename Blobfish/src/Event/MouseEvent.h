//
// Created by plasm on 14.07.2022.
//

#ifndef COMPOUND_MOUSEEVENT_H
#define COMPOUND_MOUSEEVENT_H

#include "Event.h"
#include "../Core/BlobPCH.h"

namespace Blobfish {
    class MouseButtonPressedEvent : public Event {
        int m_category = EventCategory::EMouse | EventCategory::EMouseButton | EventCategory::EInput;
        int m_mouseButton;
    public:
        MouseButtonPressedEvent(int p_mouseButton) : m_mouseButton(p_mouseButton) {}

        DECLARE_EVENT_CLASS(EventType::MouseButtonPressed)

        int getMouseButton() const {
            return m_mouseButton;
        }
    };

    class MouseButtonReleasedEvent : public Event {
        int m_category = EventCategory::EMouse | EventCategory::EMouseButton | EventCategory::EInput;
        int m_mouseButton;
    public:
        MouseButtonReleasedEvent(int p_mouseButton) : m_mouseButton(p_mouseButton) {}

        DECLARE_EVENT_CLASS(EventType::MouseButtonReleased)

        int getMouseButton() const {
            return m_mouseButton;
        }
    };

    class MouseMovedEvent : public Event {
        int m_category = EventCategory::EMouse | EventCategory::EInput;
        int m_offsetX;
        int m_offsetY;
    public:
        MouseMovedEvent(int p_offsetX, int p_OffsetY) : m_offsetX(p_offsetX), m_offsetY(p_OffsetY) {}

        DECLARE_EVENT_CLASS(EventType::MouseMoved)

        std::string ToString() const override {
            return "MouseMovedEvent: " + std::to_string(m_offsetX) + ", " + std::to_string(m_offsetY);
        }
    };

    class MouseScrolledEvent : public Event {
        int m_category = EventCategory::EMouse | EventCategory::EInput;
    public:
        MouseScrolledEvent(const float xOffset, const float yOffset)
                : m_offsetX(xOffset), m_offsetY(yOffset) {}

        DECLARE_EVENT_CLASS(EventType::MouseScrolled)

        float getOffsetX() const { return m_offsetX; }

        float getOffsetY() const { return m_offsetY; }

        std::string ToString() const override {
            return "MouseScrolledEvent: " + std::to_string(m_offsetX) + ", " + std::to_string(m_offsetY);
        }

    private:
        float m_offsetX, m_offsetY;
    };

}

#endif //COMPOUND_MOUSEEVENT_H
