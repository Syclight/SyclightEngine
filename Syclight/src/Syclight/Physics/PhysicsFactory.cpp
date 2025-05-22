#include "PhysicsFactory.h"
#include "Bullet/BulletPhysicsWorld.h"

namespace syc
{
    std::unique_ptr<IPhysicsWorld> PhysicsFactory::CreateBulletPhysicsWorld() {
        return std::make_unique<BulletPhysicsWorld>();
    }
}