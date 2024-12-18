#pragma once

class SimulatableObject
{
public:
    virtual ~SimulatableObject() = default;
    virtual void update(float deltaTime) = 0;
};

class Particle : public SimulatableObject
{
private:
    float position, velocity, gravity = 9.81f;
public:
    Particle(float position, float velocity);
    ~Particle();
    void update(float deltaTime) override;
};
 