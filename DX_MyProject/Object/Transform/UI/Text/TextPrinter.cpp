#include "framework.h"

TextPrinter::TextPrinter(Vector2 inSize, Vector2 inScale, Vector2 inOffset)
	:UI(inSize,inScale,inOffset)
	,lineLength(10),textIdx(0)
	,charScale(Vector2(0,0)),charPos(Vector2(0,0))
	, charInterval(Vector2(0,0))
	,printStr("")
{
	for (int i = 0; i < 5; i++)
	{
		Text* text = new Text();
		text->SetID(UI_ID::TEXT);
		text->SetTarget(this);
		text->SetScale(charScale);
		textList.push_back(text);
		childList.push_back(text);
	}
	id = UI_ID::TEXT_PRINTER;
	type = UI_TYPE::TEXT;
	is_active = false;
}

TextPrinter::~TextPrinter()
{
}

void TextPrinter::Update()
{
	if (!is_active)return;

	if(target!=nullptr)
		pos = target->pos + offset;
	WorldUpdate();

	for (auto c : childList)
		c->Update();
}

void TextPrinter::Render()
{
	if (!is_active)return;

	for (auto c : childList)
		c->Render();
}

void TextPrinter::SetID(UI::UI_ID id)
{
	this->id = id;
}

void TextPrinter::SetText(string str)
{
	printStr = str;

	charPos = Vector2(0, 0);
	textIdx = 0;
	for (int i = 0; i < printStr.length(); i++)
	{
		if (textIdx >= textList.size())
		{
			for (int j = 0; j < 10; j++)
			{
				Text* text = new Text();
				text->SetID(UI_ID::TEXT);
				text->SetTarget(this);
				text->SetScale(charScale);
				textList.push_back(text);
				childList.push_back(text);
			}
		}

		if (printStr[i] != ' ')
		{
			textList[textIdx]->SetText(printStr[i]);
			textList[textIdx]->SetOffset(charInterval * charPos);
			textList[textIdx]->SetScale(charScale);
			textList[textIdx]->SetColor(this->CB->data.colour);
			textList[textIdx]->SetActive(true);
			textIdx++;
		}
		if (charPos.x < lineLength)
		{
			charPos.x++;
		}
		else
		{
			charPos.x = 0;
			charPos.y += 1;
		}
	}
	for (int i = textIdx; i < textList.size(); i++)
		textList[i]->SetActive(false);
}

void TextPrinter::SetTextInfo(Vector2 inCScale, Vector2 inCInterval, int inLen)
{
	this->charScale = inCScale;
	this->charInterval = inCInterval;
	this->lineLength = inLen;
}

void TextPrinter::SetLineLength(int inLen)
{
	lineLength = inLen;
}

void TextPrinter::SetCharScale(Vector2 inCScale)
{
	charScale = inCScale;
}

void TextPrinter::SetCharInterval(Vector2 inInterval)
{
	charInterval = inInterval;
}
