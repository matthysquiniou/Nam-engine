#pragma once
#include "ARenderItem.h"
#include <BaseTypes.h>

constexpr int MAX_CHARS = 256;

constexpr int VERTICES_PER_CHAR = 4;
constexpr int INDICES_PER_CHAR = 6;

constexpr int MAX_TEXT_VERTICES = MAX_CHARS * VERTICES_PER_CHAR;
constexpr int MAX_TEXT_INDICES = MAX_CHARS * INDICES_PER_CHAR;

namespace nam
{
	//Setted for Pusab.dds
	struct TextSheetDatas
	{
		int textureWidth = 712, textureHeight = 768; // size of the texture
		int charWidth = 78, charHeight = 85; // size of the rects per char

		int paddingX = 5, paddingY = 5;

		int xOffsetFrom00 = 0, yOffsetFrom00 = 0; // where the first character rect begins

		int charsPerRow = 9, charsPerCol = 9; // amount of char in a row and in a column
	};

	struct Text : public ARenderItem
	{
		int m_drawLayer = 0; 

		std::string m_currentText = {};
	private:
		TextSheetDatas m_datas;

		bool m_dataSetted = false;

		DirectX::XMFLOAT2 m_offsets[256] = {};

		int m_charAmount = 0;
		int m_charAmountInLine = 0;
		int m_backSlashN_amount = 0;

		float m_kerning = 1;

		DirectX::XMFLOAT2 m_characterSize = { 24, 24 };

	public:
		Text();

		//Works for Sprite & Text (which is a sprite)
		//ex : Sprite 1 is in front of Sprite 2
		//if Sprite 1 has a lower Layer than Sprite 2
		//Layer N is in front of Layer (N + 1)
		void SetDrawLayer(int drawLayer);

		void SetText(std::string txt);
		void SetDatas(DirectX::XMFLOAT2 characterSize, float kerning, DirectX::XMFLOAT4 textColor = {1, 1, 1, 1}, TextSheetDatas* p_datas = nullptr);

		const DirectX::XMFLOAT2& GetCharacterSize() const;
		const float& GetKerning() const;

		void ChangeKerning(float kerning);
		void SetCharacterSize(DirectX::XMFLOAT2 size);

	private:
		void AddRect(DirectX::XMFLOAT4 color, char c);
	};
}

