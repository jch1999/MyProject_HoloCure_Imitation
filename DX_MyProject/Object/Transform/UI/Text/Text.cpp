#include "framework.h"

int& Text::GetTextUseCnt()
{
	static int textUseCnt = 0;
	return;
}

unordered_map<char, shared_ptr<const Frame>>& Text::GetTextFrameMap()
{
	static unordered_map<char, shared_ptr<const Frame>> textFrameMap;
	return textFrameMap;
}

unordered_map<char, Vector2>& Text::GetTextSizeMap()
{
	static unordered_map<char, Vector2> textSizeMap;
	return textSizeMap;
}

Text::Text(Vector2 inSize,Vector2 inScale,Vector2 inOffset)
	:UI(inSize,inScale,inOffset)
{	
	if (GetTextFrameMap().empty())
	{
		InitFrame();
	}

	id = UI_ID::LEVEL_TEXT;
	type = UI_TYPE::TEXT;
	SetText('0');
	is_active = false;

	++GetTextUseCnt();
}

Text::~Text()
{
	if ((--GetTextUseCnt()) == 0)
	{
		ClearFrame();
		RemoveTextInfo();
	}
}

void Text::Update()
{
	if (!is_active)return;

	auto& currentFrame = GetTextFrameMap()[c];
	scale = currentFrame->GetFrameSize() * uiSize / currentFrame->GetFrameOriginSize() * uiScale;

	pos = target->pos + offset;
	WorldUpdate();
}

void Text::Render()
{
	if (!is_active)return;
	VS->Set();
	PS->Set();

	WB->SetVS(0);
	CB->SetPS(0);

	GetTextFrameMap()[c]->Render();
}

void Text::PostRender()
{
}

void Text::InitFrame()
{
	auto& textFrameMap = GetTextFrameMap();
	auto& textSizeMap = GetTextSizeMap();
	if (!(textFrameMap.empty())) return;

	wstring file = L"Textures/Text/PC Computer - LEGO Star Wars The Complete Saga - Font.png";
	// number text frame
	for (int i = 0; i < 10; i++)
	{
		char nowChar = '0' + i;
		textFrameMap[nowChar] = make_shared<const Frame>(file, i * 32.0f, 242.0f, 32.0f, 40.0f);
		textSizeMap[nowChar] = Vector2(32.0f, 40.0f);;
	}
	// Capital frame
	{
		// A
		textFrameMap['A'] = make_shared<const Frame>(file, 2.0f, 3.0f, 35.0f, 38.0f);
		textSizeMap['A'] = Vector2(35.0f, 38.0f);
		// B
		textFrameMap['B'] = make_shared<const Frame>(file, 39.0f, 3.0f, 31.0f, 38.0f);
		textSizeMap['B'] = Vector2(31.0f, 38.0f);
		// C
		textFrameMap['C'] = make_shared<const Frame>(file, 73.0f, 2.0f, 32.0f, 40.0f);
		textSizeMap['C'] = Vector2(32.0f, 40.0f);
		// D
		textFrameMap['D'] = make_shared<const Frame>(file, 112.0f, 3.0f, 33.0f, 38.0f);
		textSizeMap['D'] = Vector2(33.0f, 38.0f);
		// E
		textFrameMap['E'] = make_shared<const Frame>(file, 153.0f, 3.0f, 28.0f, 38.0f);
		textSizeMap['E'] = Vector2(28.0f, 38.0f);
		// F
		textFrameMap['F'] = make_shared<const Frame>(file, 188.0f, 3.0f, 27.0f, 38.0f);
		textSizeMap['F'] = Vector2(27.0f, 38.0f);
		// G
		textFrameMap['G'] = make_shared<const Frame>(file, 220.0f, 2.0f, 33.0f, 40.0f);
		textSizeMap['G'] = Vector2(33.0f, 40.0f);
		// H
		textFrameMap['H'] = make_shared<const Frame>(file, 262.0f, 3.0f, 31.0f, 38.0f);
		textSizeMap['H'] = Vector2(31.0f, 38.0f);
		// I
		textFrameMap['I'] = make_shared<const Frame>(file, 303.0f, 3.0f, 13.0f, 38.0f);
		textSizeMap['I'] = Vector2(13.0f, 38.0f);
		// J
		textFrameMap['J'] = make_shared<const Frame>(file, 322.0f, 3.0f, 21.0f, 39.0f);
		textSizeMap['J'] = Vector2(21.0f, 39.0f);
		// K
		textFrameMap['K'] = make_shared<const Frame>(file, 353.0f, 3.0f, 32.0f, 38.0f);
		textSizeMap['K'] = Vector2(32.0f, 38.0f);
		// L
		textFrameMap['L'] = make_shared<const Frame>(file, 392.0f, 3.0f, 27.0f, 38.0f);
		textSizeMap['L'] = Vector2(27.0f, 38.0f);
		// M
		textFrameMap['M'] = make_shared<const Frame>(file, 3.0f, 51.0f, 38.0f, 38.0f);
		textSizeMap['M'] = Vector2(38.0f, 38.0f);
		// N
		textFrameMap['N'] = make_shared<const Frame>(file, 44.0f, 51.0f, 31.0f, 38.0f);
		textSizeMap['N'] = Vector2(31.0f, 38.0f);
		// O
		textFrameMap['O'] = make_shared<const Frame>(file, 78.0f, 50.0f, 35.0f, 40.0f);
		textSizeMap['O'] = Vector2(35.0f, 40.0f);
		// P
		textFrameMap['P'] = make_shared<const Frame>(file, 116.0f, 51.0f, 31.0f, 38.0f);
		textSizeMap['P'] = Vector2(31.0f, 38.0f);
		// Q
		textFrameMap['Q'] = make_shared<const Frame>(file, 153.0f, 50.0f, 35.0f, 46.0f);
		textSizeMap['Q'] = Vector2(35.0f, 46.0f);
		// R
		textFrameMap['R'] = make_shared<const Frame>(file, 195.0f, 51.0f, 32.0f, 38.0f);
		textSizeMap['R'] = Vector2(32.0f, 38.0f);
		// S
		textFrameMap['S'] = make_shared<const Frame>(file, 233.0f, 50.0f, 32.0f, 40.0f);
		textSizeMap['S'] = Vector2(32.0f, 40.0f);
		// T
		textFrameMap['T'] = make_shared<const Frame>(file, 270.0f, 51.0f, 30.0f, 38.0f);
		textSizeMap['T'] = Vector2(30.0f, 38.0f);
		// U
		textFrameMap['U'] = make_shared<const Frame>(file, 305.0f, 51.0f, 29.0f, 39.0f);
		textSizeMap['U'] = Vector2(29.0f, 39.0f);
		// V
		textFrameMap['V'] = make_shared<const Frame>(file, 341.0f, 51.0f, 32.0f, 38.0f);
		textSizeMap['V'] = Vector2(32.0f, 38.0f);
		// W
		textFrameMap['W'] = make_shared<const Frame>(file, 375.0f, 51.0f, 48.0f, 38.0f);
		textSizeMap['W'] = Vector2(48.0f, 38.0f);
		// X
		textFrameMap['X'] = make_shared<const Frame>(file, 10.0f, 99.0f, 33.0f, 38.0f);
		textSizeMap['X'] = Vector2(33.0f, 38.0f);
		// Y
		textFrameMap['Y'] = make_shared<const Frame>(file, 46.0f, 99.0f, 34.0f, 38.0f);
		textSizeMap['Y'] = Vector2(34.0f, 38.0f);
		// Z
		textFrameMap['Z'] = make_shared<const Frame>(file, 83.0f, 99.0f, 30.0f, 38.0f);
		textSizeMap['Z'] = Vector2(30.0f, 38.0f);
	}
	// small clip // 36 ~61
	{
		// a
		textFrameMap['a'] = make_shared<const Frame>(file, 1.0f, 146.0f, 29.0f, 46.0f);
		textSizeMap['a'] = Vector2(29.0f, 46.0f);
		// b
		textFrameMap['b'] = make_shared<const Frame>(file, 31.0f, 146.0f, 27.0f, 46.0f);
		textSizeMap['b'] = Vector2(27.0f, 46.0f);
		// c
		textFrameMap['c'] = make_shared<const Frame>(file, 59.0f, 146.0f, 26.0f, 46.0f);
		textSizeMap['c'] = Vector2(26.0f, 46.0f);
		// d
		textFrameMap['d'] = make_shared<const Frame>(file, 87.0f, 146.0f, 27.0f, 46.0f);
		textSizeMap['d'] = Vector2(27.0f, 46.0f);
		// e
		textFrameMap['e'] = make_shared<const Frame>(file, 116.0f, 146.0f, 28.0f, 46.0f);
		textSizeMap['e'] = Vector2(28.0f, 46.0f);
		// f
		textFrameMap['f'] = make_shared<const Frame>(file, 145.0f, 146.0f, 21.0f, 46.0f);
		textSizeMap['f'] = Vector2(21.0f, 46.0f);
		// g
		textFrameMap['g'] = make_shared<const Frame>(file, 167.0f, 146.0f, 30.0f, 46.0f);
		textSizeMap['g'] = Vector2(30.0f, 46.0f);
		// h
		textFrameMap['h'] = make_shared<const Frame>(file, 198.0f, 146.0f, 26.0f, 46.0f);
		textSizeMap['h'] = Vector2(26.0f, 46.0f);
		// i
		textFrameMap['i'] = make_shared<const Frame>(file, 225.0f, 146.0f, 12.0f, 46.0f);
		textSizeMap['i'] = Vector2(12.0f, 46.0f);
		// j
		textFrameMap['j'] = make_shared<const Frame>(file, 238.0f, 146.0f, 18.0f, 46.0f);
		textSizeMap['j'] = Vector2(18.0f, 46.0f);
		// k
		textFrameMap['k'] = make_shared<const Frame>(file, 257.0f, 146.0f, 28.0f, 46.0f);
		textSizeMap['k'] = Vector2(28.0f, 46.0f);
		// l
		textFrameMap['l'] = make_shared<const Frame>(file, 286.0f, 146.0f, 12.0f, 46.0f);
		textSizeMap['l'] = Vector2(12.0f, 46.0f);
		// m
		textFrameMap['m'] = make_shared<const Frame>(file, 299.0f, 146.0f, 42.0f, 46.0f);
		textSizeMap['m'] = Vector2(42.0f, 46.0f);
		// n
		textFrameMap['n'] = make_shared<const Frame>(file, 342.0f, 146.0f, 26.0f, 46.0f);
		textSizeMap['n'] = Vector2(26.0f, 46.0f);
		// o
		textFrameMap['o'] = make_shared<const Frame>(file, 1.0f, 194.0f, 28.0f, 46.0f);
		textSizeMap['o'] = Vector2(28.0f, 46.0f);
		// p
		textFrameMap['p'] = make_shared<const Frame>(file, 30.0f, 194.0f, 27.0f, 46.0f);
		textSizeMap['p'] = Vector2(27.0f, 46.0f);
		// q
		textFrameMap['q'] = make_shared<const Frame>(file, 58.0f, 194.0f, 28.0f, 46.0f);
		textSizeMap['q'] = Vector2(28.0f, 46.0f);
		// r
		textFrameMap['r'] = make_shared<const Frame>(file, 87.0f, 194.0f, 18.0f, 46.0f);
		textSizeMap['r'] = Vector2(18.0f, 46.0f);
		// s
		textFrameMap['s'] = make_shared<const Frame>(file, 106.0f, 194.0f, 27.0f, 46.0f);
		textSizeMap['s'] = Vector2(27.0f, 46.0f);
		// t
		textFrameMap['t'] = make_shared<const Frame>(file, 134.0f, 194.0f, 20.0f, 46.0f);
		textSizeMap['t'] = Vector2(20.0f, 46.0f);
		// u
		textFrameMap['u'] = make_shared<const Frame>(file, 155.0f, 194.0f, 26.0f, 46.0f);
		textSizeMap['u'] = Vector2(26.0f, 46.0f);
		// v
		textFrameMap['v'] = make_shared<const Frame>(file, 182.0f, 190.0f, 27.0f, 46.0f);
		textSizeMap['v'] = Vector2(27.0f, 46.0f);
		// w
		textFrameMap['w'] = make_shared<const Frame>(file, 210.0f, 194.0f, 39.0f, 46.0f);
		textSizeMap['w'] = Vector2(39.0f, 46.0f);
		// x
		textFrameMap['x'] = make_shared<const Frame>(file, 250.0f, 194.0f, 27.0f, 46.0f);
		textSizeMap['x'] = Vector2(27.0f, 46.0f);
		// y
		textFrameMap['y'] = make_shared<const Frame>(file, 278.0f, 194.0f, 26.0f, 46.0f);
		textSizeMap['y'] = Vector2(26.0f, 46.0f);
		// z
		textFrameMap['z'] = make_shared<const Frame>(file, 305.0f, 194.0f, 24.0f, 46.0f);
		textSizeMap['z'] = Vector2(24.0f, 46.0f);
	}

	// Extra clip
	{
		// ':' // 62
		textFrameMap[':'] = make_shared<const Frame>(file, 29.0f, 289.0f, 12.0f, 46.0f);
		textSizeMap[':'] = Vector2(12.0f, 46.0f);
		// '/' // 63
		textFrameMap['/'] = make_shared<const Frame>(file, 42.0f, 289.0f, 31.0f, 46.0f);
		textSizeMap['/'] = Vector2(31.0f, 46.0f);
		// '+' //64
		textFrameMap['+'] = make_shared<const Frame>(file, 77.0f, 375.0f, 30.0f, 46.0f);
		textSizeMap['+'] = Vector2(31.0f, 46.0f);
		// '' //65
		textFrameMap['-'] = make_shared<const Frame>(file, 75.0f, 290.0f, 30.0f, 46.0f);
		textSizeMap['-'] = Vector2(18.0f, 46.0f);
		// '%' // 66
		textFrameMap['%'] = make_shared<const Frame>(file, 220.0f, 287.0f, 40.0f, 46.0f);
		textSizeMap['%'] = Vector2(40.0f, 46.0f);
		// '.' //67
		textFrameMap['.'] = make_shared<const Frame>(file, 2.0f, 283.0f, 12.0f, 46.0f);
		textSizeMap['.'] = Vector2(12.0f, 46.0f);
		// ',' // 68
		textFrameMap[','] = make_shared<const Frame>(file, 15.0f, 289.0f, 13.0f, 46.0f);
		textSizeMap[','] = Vector2(13.0f, 46.0f);
		// '!' // 69
		textFrameMap['!'] = make_shared<const Frame>(file, 123.0f, 287.0f, 14.0f, 46.0f);
		textSizeMap['!'] = Vector2(13.0f, 46.0f);
		// '<', '>' // 70 71
		textFrameMap['<'] = make_shared<const Frame>(file, 330.0f, 287.0f, 29.0f, 46.0f);
		textSizeMap['<'] = Vector2(29.0f, 46.0f);
		textFrameMap['>'] = make_shared<const Frame>(file, 358.0f, 287.0f, 29.0f, 46.0f);
		textSizeMap['>'] = Vector2(29.0f, 46.0f);
		// ''' // 72
		textFrameMap['\''] = make_shared<const Frame>(file, 362.0f, 432.0f, 13.0f, 46.0f);
		textSizeMap['\''] = Vector2(15.0f, 46.0f);
	}
}

void Text::ClearFrame()
{
	GetTextFrameMap().clear();
}

void Text::SetID(UI::UI_ID id)
{
}

void Text::SetClipIdx(int idx)
{
	clipIdx = idx;
}

void Text::SetText(char c)
{
	this->c = c;

	uiSize = GetTextSizeMap()[c];
}

Vector2 Text::GetTextSize()
{
	return uiSize * uiScale;
}

void Text::RemoveTextInfo()
{
	GetTextSizeMap().clear();
}
