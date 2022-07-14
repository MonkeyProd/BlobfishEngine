//
// Created by plasm on 14.07.2022.
//

#ifndef COMPOUND_LAYER_H
#define COMPOUND_LAYER_H

#include "BlobPCH.h"
#include "../Event/Event.h"
#include "Timestep.h"

namespace Blobfish {

    class Layer {
    public:
        Layer(const std::string &name = "Layer") : m_DebugName(name) {}

        virtual ~Layer() = default;

        virtual void OnAttach() { BLOB_LOG_TRACE("Layer '{0}' attach", m_DebugName);}

        virtual void OnDetach() {BLOB_LOG_TRACE("Layer '{0}' detach", m_DebugName);}

        virtual void OnUpdate(Timestep ts) {}

        virtual void OnImGuiRender() {}

        virtual void OnEvent(Event &event) {BLOB_LOG_TRACE("Layer '{0}' event {1}", m_DebugName, event);}

        const std::string &GetName() const { return m_DebugName; }

    protected:
        std::string m_DebugName;
    };

} // Blobfish

#endif //COMPOUND_LAYER_H
