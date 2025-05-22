#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <Syclight/Core/Base.h>

namespace syc {
    class SYC_API IRigidBody {
    public:
        virtual ~IRigidBody() = default;

        virtual void_ ApplyForce(const glm::vec3& force) = 0;
        virtual glm::vec3 GetPosition() const = 0;
        virtual glm::quat GetRotation() const = 0;
    };
}
