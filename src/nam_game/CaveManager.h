#pragma once
#include <CaveGenerator.h>
class CaveManager : public GameObject
{
public:
	CaveGenerator* mp_caveGenerator = nullptr;
	CaveGeneratorParams m_caveGeneratorParams = {};
	CaveSectionParams m_caveSectionParams = {};
	Vector<XMFLOAT3> m_pointList = {};
	size m_currentPoint = 0;
	RailGenerator* mp_railGenerator = nullptr;
public:
	static void Create(Scene* scene, const CaveGeneratorParams& caveGeneratorParams, const CaveSectionParams& caveSectionParams);

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;
	void SpawnCave();
	void CheckDeleteCave();
	size GetPointWithIndexOffset(int offset);
};

