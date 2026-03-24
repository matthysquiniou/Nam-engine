#pragma once
#include "SparseSet.h"

namespace nam
{
	template<typename DenseType>
	inline SparseSet<DenseType>::SparseSet(size sparseSize)
	{
		m_entityToPageIndex.resize(sparseSize, { INVALID_PAGE, 0 });
	}

	template<typename DenseType>
	SparseSet<DenseType>::~SparseSet() {
	}

	template<typename DenseType>
	inline bool SparseSet<DenseType>::Add(const u32 id, const DenseType& denseType)
	{
		if (Has(id))
			return false;

		u32 pageIndex = 0;
		while (pageIndex < m_pages.size())
		{
			if (m_pages[pageIndex].m_count < SparseSetPage<DenseType>::PAGE_SIZE)
				break;
			pageIndex++;
		}

		if (pageIndex == m_pages.size()) {
			m_pages.emplace_back();
		}

		SparseSetPage<DenseType>& page = m_pages[pageIndex];
		u32 localIndex = page.m_count;

		page.m_data[localIndex] = denseType;
		page.m_entities[localIndex] = id;
		page.m_count++;

		m_entityToPageIndex[id] = { pageIndex, localIndex };

		return true;
	}

	template<typename DenseType>
	inline bool SparseSet<DenseType>::Remove(const u32 id)
	{
		if (!Has(id))
			return false;

		const PageIndex& pageIndex = m_entityToPageIndex[id];
		SparseSetPage<DenseType>& page = m_pages[pageIndex.m_pageIndex];
		u32 lastIndex = page.m_count - 1;

		if (pageIndex.m_localIndex != lastIndex) {
			u32 lastEntity = page.m_entities[lastIndex];

			page.m_data[pageIndex.m_localIndex] = std::move(page.m_data[lastIndex]);
			page.m_entities[pageIndex.m_localIndex] = lastEntity;

			m_entityToPageIndex[lastEntity].m_localIndex = pageIndex.m_localIndex;
		}

		page.m_count--;
		m_entityToPageIndex[id] = { INVALID_PAGE, 0 };

		return true;
	}

	template<typename DenseType>
	inline bool SparseSet<DenseType>::Has(const u32 id) const
	{
		assert(id < m_entityToPageIndex.size());
		return m_entityToPageIndex[id].m_pageIndex != INVALID_PAGE;
	}

	template<typename DenseType>
	inline const DenseType& SparseSet<DenseType>::Get(const u32 id) const
	{
		assert(Has(id) && "sparse doesn't know the entity");
		const PageIndex& pageIndex = m_entityToPageIndex[id];
		return m_pages[pageIndex.m_pageIndex].m_data[pageIndex.m_localIndex];
	}

	template<typename DenseType>
	inline DenseType& SparseSet<DenseType>::Get(const u32 id)
	{
		assert(Has(id) && "sparse doesn't know the entity");
		const PageIndex& pageIndex = m_entityToPageIndex[id];
		return m_pages[pageIndex.m_pageIndex].m_data[pageIndex.m_localIndex];
	}


	template<typename DenseType>
	inline Vector<u32> SparseSet<DenseType>::GetEntities() const
	{
		Vector<u32> entities;
		entities.reserve(Size());

		for (const auto& page : m_pages) {
			for (u32 j = 0; j < page.m_count; ++j) {
				entities.push_back(page.m_entities[j]);
			}
		}
		return entities;
	}

	template<typename DenseType>
	inline const size SparseSet<DenseType>::Size() const
	{
		size total = 0;
		for (const auto& page : m_pages) {
			total += page.m_count;
		}
		return total;
	}
}