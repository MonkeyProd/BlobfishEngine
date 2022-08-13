#ifndef COMPOUND_SERIALIZER_H
#define COMPOUND_SERIALIZER_H

#include "Scene.h"
#include "Entity.h"

namespace bf {

    class Serializer {
    public:
        Serializer(Scene *scene);
        void Serialize(const std::string &path);
        void Deserialize(const std::string& filepath); // TODO mb return bool as a signal of deserialization success
    private:
        void SerializeEntity(Entity &entity);
        Scene *m_scene;
    };

} // bf

#endif //COMPOUND_SERIALIZER_H
