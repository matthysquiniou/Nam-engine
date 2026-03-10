#include "pch.h"
#include "RailGenerator.h"
#include <PointHasher.h>

RailData::RailData()
{
	m_posRight = XMFLOAT3(0.f, 0.f, 0.f);
	m_posLeft = XMFLOAT3(0.f, 0.f, 0.f);
	m_scaleOffset = XMFLOAT3(1.f, 1.f, 1.f);
}

RailData::RailData(XMFLOAT3 posLeft, XMFLOAT3 posRight, XMFLOAT3 scaleOffset)
{
	m_posRight = posRight;
	m_posLeft = posLeft;
	m_scaleOffset = scaleOffset;
}

RailGenerator::RailGenerator() : m_mesh(nullptr)
{
}

void RailGenerator::OnInit()
{
	//SetBehavior();
	AddComponent<RailGeneratorTag>(RailGeneratorTag());
	SetTag((int)Tag::_Rail);
}

void RailGenerator::OnStart()
{
}

void RailGenerator::OnUpdate()
{
	//App* app = App::Get();
	//float dt = app->GetChrono().GetScaledDeltaTime();
	
}

void RailGenerator::OnDestroy()
{

}

UnMap<u64, Rail*>& RailGenerator::GetMapRails()
{
	return m_mapRails;
}

void RailGenerator::SetRails(const Vector<RailData>& allBiPos)
{
	m_allRailData = allBiPos;
}

void RailGenerator::GenerateRails()
{
	for (size i = 1; i < m_allRailData.size(); i++)
	{
		

		RailData& railData = m_allRailData[i];
		XMVECTOR posRailXM = GetCenterOfRail(XMLoadFloat3(&railData.m_posRight), XMLoadFloat3(&railData.m_posLeft));
		XMFLOAT3 posRail;
		XMStoreFloat3(&posRail, posRailXM);


		RailData& railDataPrev = m_allRailData[i-1];
		XMVECTOR posRailPrevXM = GetCenterOfRail(XMLoadFloat3(&railDataPrev.m_posRight), XMLoadFloat3(&railDataPrev.m_posLeft));
		

		XMFLOAT3 multiply = XMFLOAT3(0.5f, 1.f, 1.f);
		XMVECTOR diffPosXM = XMVectorSubtract((FXMVECTOR)posRailXM, (FXMVECTOR)posRailPrevXM);
		diffPosXM = XMVectorMultiply(diffPosXM, XMLoadFloat3(&multiply));

		XMFLOAT3 forward = GetRailForward(posRailPrevXM, posRailXM);
		if (forward.y > 0 && forward.y < 1)
		{
			XMFLOAT3 diffPos;
			XMStoreFloat3(&diffPos, diffPosXM);
			posRail.y -= diffPos.y * 0.5f;
		}

		XMFLOAT3 scaleRail = railData.m_scaleOffset;
		scaleRail.z = XMVectorGetX(XMVector3Length(diffPosXM));

		m_allRails.back().push_back(CreateRail(GetScene(), posRail, forward, scaleRail, m_mesh));
	}
}

void RailGenerator::BeginGeneration()
{
	m_allRails.push({});
}

void RailGenerator::PopGeneration()
{
	if (m_allRails.empty())
		return;

	Vector<Rail*>& rails = m_allRails.front();
	for (size_t i = 0; i < rails.size(); i++)
	{
		Rail* rail = rails[i];
		GetScene()->DestroyGameObject(rail);
		m_mapRails.erase(m_fifoMapIndex);
		m_fifoMapIndex++;
	}

	m_allRails.pop();
}

Rail* RailGenerator::CreateRail(Scene* scene, const XMFLOAT3& position, const XMFLOAT3& forward, const XMFLOAT3& scale, Mesh* mesh)
{
	Rail* rail = App::Get()->CreateGameObject<Rail>(scene);
	rail->SetWorldPosition(position);
	rail->LookToWorld(forward);
	rail->SetWorldScale(scale);
	//rail->SetMesh(mesh);
	rail->Start();
	rail->SetActiveEntity(true);
	m_mapRails[m_nextMapIndex] = rail;
	m_nextMapIndex++;
	return rail;
}

XMFLOAT3 RailGenerator::GetRailForward(XMVECTOR posCenterPrev, XMVECTOR posCenterCurrent)
{
	XMFLOAT3 forward;
	XMVECTOR f = XMVectorSubtract((FXMVECTOR)posCenterCurrent, (FXMVECTOR)posCenterPrev);
	f = XMVector3Normalize(f);

	XMStoreFloat3(&forward, f);
	return forward;
}

XMVECTOR RailGenerator::GetCenterOfRail(XMVECTOR posRailRight, XMVECTOR posRailLeft)
{
	return XMVectorScale(XMVectorAdd(posRailLeft, posRailRight), 0.5f);
}

void RailGenerator::SetMeshRail(Mesh* mesh)
{
	m_mesh = mesh;
}