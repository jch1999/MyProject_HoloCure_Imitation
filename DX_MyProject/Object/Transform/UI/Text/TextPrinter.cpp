#include "framework.h"

TextPrinter::TextPrinter()
	:lineLength(10),textIdx(0)
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
		child_list.push_back(text);
	}
	id = UI_ID::TEXT_PRINTER;
	type = UI_TYPE::TEXT;
	ui_scale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

TextPrinter::~TextPrinter()
{
}

void TextPrinter::Update()
{
	if (!is_active)return;

	pos = target->pos + offset;
	WorldUpdate();

	for (auto c : child_list)
		c->Update();
}

void TextPrinter::Render()
{
	if (!is_active)return;

	for (auto c : child_list)
		c->Render();
}

void TextPrinter::PostRender()
{
}

void TextPrinter::SetState(UI::UI_STATE state)
{
	this->state = state;
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
				child_list.push_back(text);
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
