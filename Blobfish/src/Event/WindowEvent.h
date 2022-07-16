//
// Created by plasm on 14.07.2022.
//

#ifndef COMPOUND_WINDOWEVENT_H
#define COMPOUND_WINDOWEVENT_H

#include "Event.h"
#include "../Core/BlobPCH.h"

namespace bf {
    class WindowCloseEvent:public Event{
        int m_category = EventCategory::EWindow;
    public:
        DECLARE_EVENT_CLASS(EventType::WindowClose)
    };

    class WindowResizeEvent:public Event{
        int m_category = EventCategory::EWindow;
        int m_height;
        int m_width;
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
                : m_width(width), m_height(height) {}
        DECLARE_EVENT_CLASS(EventType::WindowResize)
        int getHeight() const{
            return m_height;
        }
        int getWidth() const{
            return m_width;
        }

        std::string ToString() const override
        {
            return "WindowResizeEvent: " + std::to_string(m_width)+ ", " + std::to_string(m_height);
        }
    };

}
#endif //COMPOUND_WINDOWEVENT_H
