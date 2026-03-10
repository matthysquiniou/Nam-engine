#include "pch.h"
#include "Text.h"

#include "RenderManager.h"
#include "CommandManager.h"

#include "Constants.h"

namespace nam
{
	Text::Text()
	{
		m_type = RenderItemType::_Text;
		m_psoToUse = PsoType::_Render2D;
	}

	void Text::SetDrawLayer(int drawLayer)
	{
		m_drawLayer = drawLayer;
	}

	void Text::SetText(std::string txt)
	{
		m_dirty = true;

		m_charAmount = 0;
		m_charAmountInLine = 0;
		m_backSlashN_amount = 0;

		m_vertices.clear();
		m_indices.clear();

		m_vbByteSize = 0,
		m_ibByteSize = 0;

		if (m_dataSetted == false)
		{
			_ASSERT(false && "SetData Text first !");
			return;
		}

		for (char& c : txt)
		{
			AddRect({ 1, 1, 1, 1 }, c);
		}

		m_currentText = txt;
	}

	void Text::SetDatas(XMFLOAT2 characterSize, float kerning, XMFLOAT4 textColor, TextSheetDatas* p_datas)
	{
		if(p_datas != nullptr)
			m_datas = *p_datas;

		m_dataSetted = true;
		m_kerning = kerning;
		m_characterSize = characterSize;
		m_color = textColor;

		SetTexture(_FontPusab);

		for (size_t i = 0; i < 256; i++)
		{
			m_offsets[i] = { -1, -1 };
		}

		int startIndex = 0;

		for (int c = 'A'; c <= 'Z'; c++)
		{
			int posX = startIndex % m_datas.charsPerRow;
			int posY = startIndex / m_datas.charsPerRow;

			m_offsets[c] = { (float)posX, (float)posY };

			startIndex++;
		}

		startIndex++;

		for (int c = 'a'; c <= 'z'; c++)
		{
			int posX = startIndex % m_datas.charsPerRow;
			int posY = startIndex / m_datas.charsPerRow;

			m_offsets[c] = { (float)posX, (float)posY };

			startIndex++;
		}

		startIndex++;

		for (int c = '0'; c <= '9'; c++)
		{
			int posX = startIndex % m_datas.charsPerRow;
			int posY = startIndex / m_datas.charsPerRow;

			m_offsets[c] = { (float)posX, (float)posY };

			startIndex++;
		}

		int posX = startIndex % m_datas.charsPerRow;
		int posY = startIndex / m_datas.charsPerRow;

		//Manual because not in order
		m_offsets['.'] = { (float)posX, (float)posY};
		m_offsets[','] = { (float)posX + 1, (float)posY };

		m_offsets[';'] = { (float)posX + 2, (float)posY };
		m_offsets[':'] = { (float)posX + 3, (float)posY };

		m_offsets['\''] = {(float)posX + 6, (float)posY};
		m_offsets['!'] = { (float)posX + 7, (float)posY };
		m_offsets['"'] = { (float)posX - 1, (float)posY + 1 };
			
		m_offsets['/'] = { (float)posX, (float)posY + 1};
		m_offsets['?'] = { (float)posX + 1, (float)posY + 1};
		m_offsets['%'] = { (float)posX + 2, (float)posY + 1};
		m_offsets['&'] = { (float)posX + 3, (float)posY + 1};

		m_offsets['('] = { (float)posX + 4, (float)posY + 1};
		m_offsets[')'] = { (float)posX + 5, (float)posY + 1};
		m_offsets['@'] = { (float)posX + 6, (float)posY + 1};
	}

	const DirectX::XMFLOAT2& Text::GetCharacterSize() const
	{
		return m_characterSize;
	}

	const float& Text::GetKerning() const
	{
		return m_kerning;
	}

	void Text::ChangeKerning(float kerning)
	{
		m_kerning = kerning;
		SetText(m_currentText);
	}

	void Text::SetCharacterSize(DirectX::XMFLOAT2 size)
	{
		m_characterSize = size;
		SetText(m_currentText);
	}

	void Text::AddRect(XMFLOAT4 color, char c)
	{
		if (c == '\n')
		{
			m_backSlashN_amount++;
			m_charAmountInLine = 0;
			return;
		}

		if (c == ' ')
		{
			m_charAmountInLine++;
			m_charAmount++;
			return;
		}

		if (c < 0 || c > 255)
			return;

		float xOffset = m_charAmountInLine * m_characterSize.x * m_kerning;
		float yOffset = m_backSlashN_amount * m_characterSize.y;

		u32 indicesOffset = (u32)m_vertices.size();

		XMFLOAT2 textureCharSize = { (float)m_datas.charWidth, (float)m_datas.charHeight };

		// Pos of the char in the texture
		int posX = (int)m_offsets[c].x;
		int posY = (int)m_offsets[c].y;

		int nextPosX = posX + 1;
		int nextPosY = posY + 1;

		float u0 = (float)(posX * m_datas.charWidth + m_datas.paddingX) / (float)m_datas.textureWidth;
		float v0 = (float)(posY * m_datas.charHeight + m_datas.paddingY) / (float)m_datas.textureHeight;

		float u1 = (float)((posX + 1) * m_datas.charWidth - m_datas.paddingX) / (float)m_datas.textureWidth;
		float v1 = (float)((posY + 1) * m_datas.charHeight - m_datas.paddingY) / (float)m_datas.textureHeight;

		//Build
		XMFLOAT2 h = { m_characterSize.x * 0.5f, m_characterSize.y * 0.5f };
		m_vertices.push_back(Vertex{ XMFLOAT3(-h.x + xOffset, -h.y + yOffset, 0), m_color, {u0, v0} });
		m_vertices.push_back(Vertex{ XMFLOAT3(-h.x + xOffset,  h.y + yOffset, 0), m_color, {u0, v1} });
		m_vertices.push_back(Vertex{ XMFLOAT3(h.x + xOffset,  h.y + yOffset, 0), m_color, {u1, v1} });
		m_vertices.push_back(Vertex{ XMFLOAT3(h.x + xOffset, -h.y + yOffset, 0), m_color ,{u1, v0} });

		m_charAmountInLine++;
		m_charAmount++;

		m_indices.push_back(indicesOffset);
		m_indices.push_back(indicesOffset + 1);
		m_indices.push_back(indicesOffset + 2);

		m_indices.push_back(indicesOffset + 2);
		m_indices.push_back(indicesOffset + 3);
		m_indices.push_back(indicesOffset + 0);
	}
}
