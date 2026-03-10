#pragma once

#define SPACE_BETWEEN 1.f

struct RailData
{
	XMFLOAT3 m_posRight;
	XMFLOAT3 m_posLeft;
	XMFLOAT3 m_scaleOffset;

	RailData();
	RailData(XMFLOAT3 posLeft, XMFLOAT3 posRight, XMFLOAT3 scaleOffset);
};

struct RailGeneratorTag
{
};

class RailGenerator : public GameObject
{
private:
	Vector<RailData> m_allRailData;
	Queue<Vector<Rail*>> m_allRails;
	UnMap<u64, Rail*> m_mapRails;
	Mesh* m_mesh;
	u64 m_nextMapIndex = 0;
	u64 m_fifoMapIndex = 0;

public:
	RailGenerator();

	void OnInit() override;
	void OnStart() override;
	void OnUpdate() override;
	void OnDestroy() override;

	UnMap<u64, Rail*>& GetMapRails();

	void SetRails(const Vector<RailData>& allBiPos);

	void GenerateRails();

	void BeginGeneration();
	void PopGeneration();

	Rail* CreateRail(Scene* scene, const XMFLOAT3& position, const XMFLOAT3& forward, const XMFLOAT3& scale, Mesh* mesh);

	static XMFLOAT3 GetRailForward(XMVECTOR posCenterPrev, XMVECTOR posCenterCurrent);
	static XMVECTOR GetCenterOfRail(XMVECTOR posRailFirst, XMVECTOR posRailSecond);

	void SetMeshRail(Mesh* mesh);
};




