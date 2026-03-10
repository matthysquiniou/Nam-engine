#include "pch.h"
#include "SpatialHash.h"
#include "PointHasher.h"

using namespace DirectX;

namespace nam
{
	SpatialHash::SpatialHash(float size) : cellSize(size), invCellSize(1.0f / size)
	{
	}

	void SpatialHash::Clear()
	{ 
		grid.clear();
	}

    void SpatialHash::Insert(u32 entity, const DirectX::BoundingOrientedBox& box)
    {
        DirectX::XMFLOAT3 corners[8];
        box.GetCorners(corners);

        int minX = INT_MAX;
        int maxX = INT_MIN;
        int minY = INT_MAX;
        int maxY = INT_MIN;
        int minZ = INT_MAX;
        int maxZ = INT_MIN;

        for (int i = 0; i < 8; i++) {
            int x = (int)floor(corners[i].x * invCellSize);
            int y = (int)floor(corners[i].y * invCellSize);
            int z = (int)floor(corners[i].z * invCellSize);

            minX = min(minX, x);
            maxX = max(maxX, x);
            minY = min(minY, y);
            maxY = max(maxY, y);
            minZ = min(minZ, z);
            maxZ = max(maxZ, z);
        }

        for (int x = minX; x <= maxX; x++) {
            for (int y = minY; y <= maxY; y++) {
                for (int z = minZ; z <= maxZ; z++) {
                    size h = PointHasher::Hash(x, y, z);
                    grid[h].push_back(entity);
                }
            }
        }
    }

    void SpatialHash::Insert(u32 entity, const DirectX::BoundingSphere& sphere)
    {
        int centerX = (int)floor(sphere.Center.x * invCellSize);
        int centerY = (int)floor(sphere.Center.y * invCellSize);
        int centerZ = (int)floor(sphere.Center.z * invCellSize);

        int radiusCells = (int)ceil(sphere.Radius * invCellSize);

        for (int dx = -radiusCells; dx <= radiusCells; dx++) {
            for (int dy = -radiusCells; dy <= radiusCells; dy++) {
                for (int dz = -radiusCells; dz <= radiusCells; dz++) {
                    size h = PointHasher::Hash(centerX + dx, centerY + dy, centerZ + dz);
                    grid[h].push_back(entity);
                }
            }
        }
    }

	void SpatialHash::GetNearby(u32 entity, const DirectX::XMFLOAT3& pos, Vector<u32>& result)
	{
        result.clear();
        result.reserve(64);

        int x = (int)floor(pos.x * invCellSize);
        int y = (int)floor(pos.y * invCellSize);
        int z = (int)floor(pos.z * invCellSize);

        for (int dx = -1; dx <= 1; dx++) {
            for (int dy = -1; dy <= 1; dy++) {
                for (int dz = -1; dz <= 1; dz++) {
                    size h = PointHasher::Hash(x + dx, y + dy, z + dz);
                    auto it = grid.find(h);

                    if (it != grid.end()) {
                        auto& cell = it->second;
                        for (size i = 0; i < cell.size(); i++) {
                            u32 other = cell[i];
                            result.push_back(other);
                        }
                    }
                }
            }
        }

		if (result.size() > 1) {
			std::sort(result.begin(), result.end());
			result.erase(std::unique(result.begin(), result.end()), result.end());
		}

        result.erase(std::remove(result.begin(), result.end(), entity), result.end());
	}
}