#include "pch.h"
#include "CollisionInfo.h"
using namespace DirectX;

namespace nam
{
	SingleCollisionInfo nam::CollisionInfo::GetSingleInfo(u32 entity)
	{
	
		SingleCollisionInfo sci;

		if (entity == m_entity1)
		{
			sci.m_entity = m_entity1;
			sci.m_transform = m_transform1;
			sci.m_tag = m_tag1;
			sci.m_contactPoint = m_contactPoint;
			sci.m_penetrationDepth = m_penetrationDepth;
			sci.m_normal = m_normal;
		}
		else if (entity == m_entity2)
		{
			sci.m_entity = m_entity2;
			sci.m_transform = m_transform2;
			sci.m_tag = m_tag2;
			sci.m_contactPoint = m_contactPoint;
			sci.m_penetrationDepth = m_penetrationDepth;
			XMVECTOR vNormal = XMLoadFloat3(&m_normal);
			vNormal = XMVectorScale(vNormal, -1.f);
			XMStoreFloat3(&sci.m_normal, vNormal);
		}
		return sci;
	}

}
