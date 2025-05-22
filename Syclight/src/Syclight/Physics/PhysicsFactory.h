#pragma once
#include "IPhysicsWorld.h"

namespace syc
{
	class SYC_API PhysicsFactory {
	public:
		static Scope<IPhysicsWorld> CreateBulletPhysicsWorld();
	};
}

