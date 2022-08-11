#ifndef COMPOUND_NATIVESCRIPT_H
#define COMPOUND_NATIVESCRIPT_H

#include "Entity.h"
#include <Core/Timestep.h>

// forward declaration
namespace ImGui {
    void Text(const char *fmt, ...);
}

namespace bf {

    class NativeScript {
    public:
        template<typename T>
        T &GetComponent() {
            return m_Entity.GetComponent<T>();
        }

        std::optional<Entity> Find(const std::string &Tag) {
            return m_Entity.Find(Tag);
        }

        virtual void OnImGuiRender() { ImGui::Text("Empty"); }

        virtual void OnCreate() {}

        virtual void OnDestroy() {}

        virtual void OnUpdate(Timestep ts) {}


    private:
        Entity m_Entity;

        friend class Scene;
    };

} // bf

#endif //COMPOUND_NATIVESCRIPT_H
