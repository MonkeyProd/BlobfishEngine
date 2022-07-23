#ifndef EVENT_H
#define EVENT_H

#include "../Core/BlobPCH.h"

namespace bf {

    enum class EventType : char {
        None = 0,
        WindowClose, WindowResize,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
        CustomEvent
    };

    enum EventCategory {
        ENone = 0,
        EWindow = BIT(0),
        EInput = BIT(1),
        EKeyboard = BIT(2),
        EMouse = BIT(3),
        EMouseButton = BIT(4)
    };

#define DECLARE_EVENT_CLASS(type) virtual EventType GetEventType() const override{return type;} \
    virtual const char *GetName() const override { return #type;}                               \
    virtual int GetCategoryFlags() const override {return m_category;}                          \
    static EventType GetStaticType() { return type; }

    class Event {
    protected:
        int m_category = (int) EventCategory::ENone;
    public:
        bool m_handled = false;

        virtual EventType GetEventType() const = 0;

        virtual const char *GetName() const = 0;

        virtual int GetCategoryFlags() const = 0;

        virtual std::string ToString() const { return GetName(); }

        bool IsInCategory(EventCategory category) {
            return GetCategoryFlags() & category;
        }

        virtual ~Event() = default;
    };

    inline std::ostream &operator<<(std::ostream &os, const Event &e) {
        return os << e.ToString();
    }

    class EventDispatcher {
    public:
        EventDispatcher(Event &event)
                : m_Event(event) {
        }

        // F will be deduced by the compiler
        template<typename T, typename F>
        requires std::derived_from<T, Event> and requires(T &e, F handler){
            { handler(e) } -> std::convertible_to<bool>;
        }
        bool Dispatch(const F &func) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.m_handled |= func(static_cast<T &>(m_Event));
                return true;
            }
            return false;
        }

    private:
        Event &m_Event;
    };

} // Blobfish

#endif //EVENT_H
