#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include "Layer.h"

namespace bf {

    class LayerStack {
    public:
        LayerStack() = default;

        ~LayerStack(){
            ZoneScoped;
            for (auto layer: m_Layers){
                layer->OnDetach();
                delete layer;
            }
        }

        void PushLayer(Layer *layer){
            ZoneScoped;
            m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, layer);
            m_LayerInsertIndex++;
            layer->OnAttach();
        }

        void PushOverlay(Layer *overlay){
            ZoneScoped;
            m_Layers.emplace_back(overlay);
            overlay->OnAttach();
        }

        void PopLayer(Layer *layer){
            ZoneScoped;
            auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
            if (it != m_Layers.begin() + m_LayerInsertIndex)
            {
                layer->OnDetach();
                m_Layers.erase(it);
                m_LayerInsertIndex--;
            }
            layer->OnDetach();
        }

        void PopOverlay(Layer *overlay){
            ZoneScoped;
            auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), overlay);
            if (it != m_Layers.end())
            {
                overlay->OnDetach();
                m_Layers.erase(it);
            }
            overlay->OnDetach();
        }

        std::vector<Layer *>::iterator begin() { return m_Layers.begin(); }

        std::vector<Layer *>::iterator end() { return m_Layers.end(); }

        std::vector<Layer *>::reverse_iterator rbegin() { return m_Layers.rbegin(); }

        std::vector<Layer *>::reverse_iterator rend() { return m_Layers.rend(); }

        std::vector<Layer *>::const_iterator begin() const { return m_Layers.begin(); }

        std::vector<Layer *>::const_iterator end() const { return m_Layers.end(); }

        std::vector<Layer *>::const_reverse_iterator rbegin() const { return m_Layers.rbegin(); }

        std::vector<Layer *>::const_reverse_iterator rend() const { return m_Layers.rend(); }

    private:
        std::vector<Layer *> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };

} // Blobfish

#endif //LAYERSTACK_H
