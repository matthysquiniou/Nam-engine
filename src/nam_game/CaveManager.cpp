#include "pch.h"
#include "CaveManager.h"
#include "Player.h"
#include <RenderManager.h>
#include <TextureTags.h>

void CaveManager::OnInit()
{
    m_pointList = {
        { 0.00f, 0.00f, 0.00f },
        { 49.81f, 4.35f, 2.17f },
        { 98.45f, 17.15f, 8.57f },
        { 144.78f, 37.64f, 18.82f },
        { 187.69f, 64.69f, 32.34f },
        { 226.11f, 96.79f, 48.39f },
        { 259.04f, 132.08f, 66.04f },
        { 285.53f, 168.44f, 84.22f },
        { 304.76f, 203.49f, 101.74f },
        { 316.03f, 234.61f, 117.30f },
        { 318.79f, 259.13f, 129.56f },
        { 312.63f, 274.55f, 137.27f },
        { 297.43f, 278.89f, 139.44f },
        { 273.74f, 271.18f, 135.59f },
        { 242.79f, 251.78f, 125.89f },
        { 206.18f, 222.05f, 111.02f },
        { 165.65f, 184.14f, 92.07f },
        { 123.00f, 140.75f, 70.37f },
        { 80.05f, 94.75f, 47.37f },
        { 38.58f, 48.88f, 24.44f },
        { 0.00f, 0.00f, 0.00f },
        { -38.58f, -48.88f, -24.44f },
        { -80.05f, -94.75f, -47.37f },
        { -123.00f, -140.75f, -70.37f },
        { -165.65f, -184.14f, -92.07f },
        { -206.18f, -222.05f, -111.02f },
        { -242.79f, -251.78f, -125.89f },
        { -273.74f, -271.18f, -135.59f },
        { -297.43f, -278.89f, -139.44f },
        { -312.63f, -274.55f, -137.27f },
        { -318.79f, -259.13f, -129.56f },
        { -316.03f, -234.61f, -117.30f },
        { -304.76f, -203.49f, -101.74f },
        { -285.53f, -168.44f, -84.22f },
        { -259.04f, -132.08f, -66.04f },
        { -226.11f, -96.79f, -48.39f },
        { -187.69f, -64.69f, -32.34f },
        { -144.78f, -37.64f, -18.82f },
        { -98.45f, -17.15f, -8.57f },
        { -49.81f, -4.35f, -2.17f }
    };
    SetBehavior();
}

void CaveManager::OnStart()
{
}

void CaveManager::OnUpdate()
{
    CheckDeleteCave();
    Ecs& ecs = App::Get()->GetEcs();

    ecs.ForEach<TagPlayer>(
        [&](u32 e, TagPlayer& tag) {
            Player* player = (Player*)GetScene()->GetGameObject(e);
            player->SetRailGenerator(mp_railGenerator);
        }
    );
}

void CaveManager::OnDestroy()
{
	delete mp_caveGenerator;
	mp_caveGenerator = nullptr;
}

void CaveManager::SpawnCave()
{
    size next = GetPointWithIndexOffset(1);
    mp_caveGenerator->Generate(m_caveGeneratorParams, m_pointList[m_currentPoint], m_pointList[next]);
    m_currentPoint = next;
    mp_railGenerator->BeginGeneration();
    Vector<CaveTubeSection>* caveTubes = mp_caveGenerator->GetLastTubeSections();
    if (caveTubes == nullptr)
        return;

    float railYOffset = -m_caveGeneratorParams.m_tunnelRadius + m_caveSectionParams.m_voxelSize * 3.f;

    Vector<RailData> railDatas;
    for (size i = 0; i < caveTubes->size(); i++)
    {
        CaveTubeSection& caveTube = (*caveTubes)[i];
        XMFLOAT3 start = caveTube.m_start;
        XMFLOAT3 end = caveTube.m_end;
        start.y += railYOffset;
        end.y += railYOffset;
        if (i == 0)
        {
            RailData firstRailData;
            firstRailData.m_scaleOffset = { 2.f,0.f,0.f };

            firstRailData.m_posLeft = end;
            firstRailData.m_posRight = end;
            firstRailData.m_posLeft.z -= SPACE_BETWEEN;
            firstRailData.m_posRight.z += SPACE_BETWEEN;
            railDatas.push_back(firstRailData);
        }
        RailData railData;
        railData.m_scaleOffset = { 2.f,0.f,0.f };
     
        railData.m_posLeft = end;
        railData.m_posRight = end;
        railData.m_posLeft.z -= SPACE_BETWEEN;
        railData.m_posRight.z += SPACE_BETWEEN;
        railDatas.push_back(railData);
    }

    mp_railGenerator->SetRails(railDatas);
    mp_railGenerator->GenerateRails();
}

void CaveManager::CheckDeleteCave()
{
    Ecs& ecs = App::Get()->GetEcs();
    size previous = GetPointWithIndexOffset(-1);
    XMFLOAT3 previousPoint = m_pointList[previous];
    XMFLOAT3 playerPos;
    ecs.ForEach<TagPlayer, TransformComponent>(
        [&](u32 e, TagPlayer& tag, TransformComponent& t) {
            t.UpdateWorldData();
            playerPos = t.GetWorldPosition();
        }
    );
    float distance;
    XMStoreFloat(&distance,XMVector3Length(XMVectorSubtract(XMLoadFloat3(&previousPoint), XMLoadFloat3(&playerPos))));
    float deleteDistance = 15.f;
    if (distance < deleteDistance)
    {
        mp_caveGenerator->PopGeneration();
        mp_railGenerator->PopGeneration();
        SpawnCave();
    }
}

size CaveManager::GetPointWithIndexOffset(int offset)
{
    return ((int)(m_currentPoint + offset) % m_pointList.size());
}

void CaveManager::Create(Scene* scene, const CaveGeneratorParams& caveGeneratorParams, const CaveSectionParams& caveSectionParams)
{
	CaveManager* cm = scene->CreateGameObject<CaveManager>();
	cm->mp_caveGenerator = new CaveGenerator(scene, caveSectionParams, 24);
	cm->m_caveGeneratorParams = caveGeneratorParams;
    cm->mp_railGenerator = scene->CreateGameObject<RailGenerator>();

    cm->m_caveSectionParams = caveSectionParams;
    Mesh* mesh = Render->GetRenderItemManager().CreateRenderItem<Mesh>();
    mesh->BuildPlane(XMFLOAT2(2.f, 2.f), { 1,1,1,1 }, false);
    mesh->SetTexture(_Rainbow);
    cm->mp_railGenerator->SetMeshRail(mesh);
    cm->SpawnCave();
    cm->SpawnCave();
    cm->SpawnCave();
    cm->SpawnCave();
    cm->SpawnCave();
}
