#include "framework.h"

TextPrinter::TextPrinter()
	:line_length(10),text_idx(0)
	,char_scale(Vector2(0,0)),char_pos(Vector2(0,0))
	, char_interval(Vector2(0,0))
	,printStr("")
{
	for (int i = 0; i < 5; i++)
	{
		Text* text = new Text();
		text->SetID(UI_ID::TEXT);
		text->SetTarget(this);
		text->SetScale(char_scale);
		text_list.push_back(text);
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

	char_pos = Vector2(0, 0);
	text_idx = 0;
	for (int i = 0; i < printStr.length(); i++)
	{
		if (text_idx >= text_list.size())
		{
			for (int j = 0; j < 10; j++)
			{
				Text* text = new Text();
				text->SetID(UI_ID::TEXT);
				text->SetTarget(this);
				text->SetScale(char_scale);
				text_list.push_back(text);
				child_list.push_back(text);
			}
		}

		if (printStr[i] != ' ')
		{
			text_list[text_idx]->SetText(printStr[i]);
			text_list[text_idx]->SetOffset(char_interval * char_pos);
			text_list[text_idx]->SetScale(char_scale);
			text_list[text_idx]->SetActive(true);
		}
		if (char_pos.x < line_length)
		{
			char_pos.x++;
		}
		else
		{
			char_pos.x = 0;
			char_pos.y += 1;
		}
		text_idx++;
	}
	for (int i = text_idx; i < text_list.size(); i++)
		text_list[i]->SetActive(false);
}
