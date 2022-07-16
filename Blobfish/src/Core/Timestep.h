//
// Created by plasm on 14.07.2022.
//

#ifndef COMPOUND_TIMESTEP_H
#define COMPOUND_TIMESTEP_H

namespace bf {
    class Timestep {
    public:
        Timestep(float time = 0.0f)
                : m_Time(time) {
        }

        operator float() const { return m_Time; }

        float GetSeconds() const { return m_Time; }

        float GetMilliseconds() const { return m_Time * 1000.0f; }

    private:
        float m_Time;
    };
}

#endif //COMPOUND_TIMESTEP_H
