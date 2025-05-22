#pragma once
#include <glm/glm.hpp>
#include <Syclight/Core/Base.h>

namespace syc
{
    class IRigidBody;

    class SYC_API IPhysicsWorld {
    public:
        virtual ~IPhysicsWorld() = default;

        virtual void StepSimulation(float deltaTime) = 0;
        virtual void SetGravity(const glm::vec3& gravity) = 0;
        virtual Ref<IRigidBody> CreateRigidBody(float mass, const glm::vec3& position) = 0;
    };
}

