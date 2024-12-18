#include "framework.h"

unordered_map<char, Frame*> Text::TextFrameMap;
unordered_map<char, Vector2> Text::TextSizeMap;
bool Text::bInit = false;
int Text::TextCnt = 0;

Text::Text()
{
	wstring file = L"Textures/Text/PC Computer - LEGO Star Wars The Complete Saga - Font.png";
	vector<Frame*> frames;
	
	if (!bInit)
	{
		Init();

		bInit = true;
	}

	id = UI_ID::LEVEL_TEXT;
	type = UI_TYPE::TEXT;
	SetText('0');
	ui_scale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;

	++TextCnt;
}

Text::~Text()
{
	if ((--TextCnt) == 0)
	{
		RemoveTextInfo();
	}
}

void Text::SetClipIdx(int idx)
{
	clip_idx = idx;
}

void Text::SetText(char c)
{
	this->c = c;

	frame = GetTextFrame(c);
	
	assert(frame);

	ui_size = GetTextSize(c);

}

void Text::Update()
{
	if (!is_active)return;

	assert(frame);

	scale = frame->GetFrameSize() * ui_size / frame->GetFrameOriginSize() * ui_scale;

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

	const_cast<Frame*>(frame)->Render();
}

void Text::PostRender()
{
}

void Text::SetState(UI::UI_STATE state)
{
}

void Text::SetID(UI::UI_ID id)
{
}

void Text::Init()
{
	wstring file = L"Textures/Text/PC Computer - LEGO Star Wars The Complete Saga - Font.png";
	// number text frame
	for (int i = 0; i < 10; i++)
	{
		char nowChar = '0' + i;
		TextFrameMap[nowChar] = new Frame(file, i * 32.0f, 242.0f, 32.0f, 40.0f);
		TextSizeMap[nowChar] = Vector2(32.0f, 40.0f);;
	}
	// Capital frame
	{
		// A
		TextFrameMap['A'] = new Frame(file, 2.0f, 3.0f, 35.0f, 38.0f);
		TextSizeMap['A'] = Vector2(35.0f, 38.0f);
		// B
		TextFrameMap['B'] = new Frame(file, 39.0f, 3.0f, 31.0f, 38.0f);
		TextSizeMap['B'] = Vector2(31.0f, 38.0f);
		// C
		TextFrameMap['C'] = new Frame(file, 73.0f, 2.0f, 32.0f, 40.0f);
		TextSizeMap['C'] = Vector2(32.0f, 40.0f);
		// D
		TextFrameMap['D'] = new Frame(file, 112.0f, 3.0f, 33.0f, 38.0f);
		TextSizeMap['D'] = Vector2(33.0f, 38.0f);
		// E
		TextFrameMap['E'] = new Frame(file, 153.0f, 3.0f, 28.0f, 38.0f);
		TextSizeMap['E'] = Vector2(28.0f, 38.0f);
		// F
		TextFrameMap['F'] = new Frame(file, 188.0f, 3.0f, 27.0f, 38.0f);
		TextSizeMap['F'] = Vector2(27.0f, 38.0f);
		// G
		TextFrameMap['G'] = new Frame(file, 220.0f, 2.0f, 33.0f, 40.0f);
		TextSizeMap['G'] = Vector2(33.0f, 40.0f);
		// H
		TextFrameMap['H'] = new Frame(file, 262.0f, 3.0f, 31.0f, 38.0f);
		TextSizeMap['H'] = Vector2(31.0f, 38.0f);
		// I
		TextFrameMap['I'] = new Frame(file, 303.0f, 3.0f, 13.0f, 38.0f);
		TextSizeMap['I'] = Vector2(13.0f, 38.0f);
		// J
		TextFrameMap['J'] = new Frame(file, 322.0f, 3.0f, 21.0f, 39.0f);
		TextSizeMap['J'] = Vector2(21.0f, 39.0f);
		// K
		TextFrameMap['K'] = new Frame(file, 353.0f, 3.0f, 32.0f, 38.0f);
		TextSizeMap['K'] = Vector2(32.0f, 38.0f);
		// L
		TextFrameMap['L'] = new Frame(file, 392.0f, 3.0f, 27.0f, 38.0f);
		TextSizeMap['L'] = Vector2(27.0f, 38.0f);
		// M
		TextFrameMap['M'] = new Frame(file, 3.0f, 51.0f, 38.0f, 38.0f);
		TextSizeMap['M'] = Vector2(38.0f, 38.0f);
		// N
		TextFrameMap['N'] = new Frame(file, 44.0f, 51.0f, 31.0f, 38.0f);
		TextSizeMap['N'] = Vector2(31.0f, 38.0f);
		// O
		TextFrameMap['O'] = new Frame(file, 78.0f, 50.0f, 35.0f, 40.0f);
		TextSizeMap['O'] = Vector2(35.0f, 40.0f);
		// P
		TextFrameMap['P'] = new Frame(file, 116.0f, 51.0f, 31.0f, 38.0f);
		TextSizeMap['P'] = Vector2(31.0f, 38.0f);
		// Q
		TextFrameMap['Q'] = new Frame(file, 153.0f, 50.0f, 35.0f, 46.0f);
		TextSizeMap['Q'] = Vector2(35.0f, 46.0f);
		// R
		TextFrameMap['R'] = new Frame(file, 195.0f, 51.0f, 32.0f, 38.0f);
		TextSizeMap['R'] = Vector2(32.0f, 38.0f);
		// S
		TextFrameMap['S'] = new Frame(file, 233.0f, 50.0f, 32.0f, 40.0f);
		TextSizeMap['S'] = Vector2(32.0f, 40.0f);
		// T
		TextFrameMap['T'] = new Frame(file, 270.0f, 51.0f, 30.0f, 38.0f);
		TextSizeMap['T'] = Vector2(30.0f, 38.0f);
		// U
		TextFrameMap['U'] = new Frame(file, 305.0f, 51.0f, 29.0f, 39.0f);
		TextSizeMap['U'] = Vector2(29.0f, 39.0f);
		// V
		TextFrameMap['V'] = new Frame(file, 341.0f, 51.0f, 32.0f, 38.0f);
		TextSizeMap['V'] = Vector2(32.0f, 38.0f);
		// W
		TextFrameMap['W'] = new Frame(file, 375.0f, 51.0f, 48.0f, 38.0f);
		TextSizeMap['W'] = Vector2(48.0f, 38.0f);
		// X
		TextFrameMap['X'] = new Frame(file, 10.0f, 99.0f, 33.0f, 38.0f);
		TextSizeMap['X'] = Vector2(33.0f, 38.0f);
		// Y
		TextFrameMap['Y'] = new Frame(file, 46.0f, 99.0f, 34.0f, 38.0f);
		TextSizeMap['Y'] = Vector2(34.0f, 38.0f);
		// Z
		TextFrameMap['Z'] = new Frame(file, 83.0f, 99.0f, 30.0f, 38.0f);
		TextSizeMap['Z'] = Vector2(30.0f, 38.0f);
	}
	// small clip // 36 ~61
	{
		// a
		TextFrameMap['a'] = new Frame(file, 1.0f, 146.0f, 29.0f, 46.0f);
		TextSizeMap['a'] = Vector2(29.0f, 46.0f);
		// b
		TextFrameMap['b'] = new Frame(file, 31.0f, 146.0f, 27.0f, 46.0f);
		TextSizeMap['b'] = Vector2(27.0f, 46.0f);
		// c
		TextFrameMap['c'] = new Frame(file, 59.0f, 146.0f, 26.0f, 46.0f);
		TextSizeMap['c'] = Vector2(26.0f, 46.0f);
		// d
		TextFrameMap['d'] = new Frame(file, 87.0f, 146.0f, 27.0f, 46.0f);
		TextSizeMap['d'] = Vector2(27.0f, 46.0f);
		// e
		TextFrameMap['e'] = new Frame(file, 116.0f, 146.0f, 28.0f, 46.0f);
		TextSizeMap['e'] = Vector2(28.0f, 46.0f);
		// f
		TextFrameMap['f'] = new Frame(file, 145.0f, 146.0f, 21.0f, 46.0f);
		TextSizeMap['f'] = Vector2(21.0f, 46.0f);
		// g
		TextFrameMap['g'] = new Frame(file, 167.0f, 146.0f, 30.0f, 46.0f);
		TextSizeMap['g'] = Vector2(30.0f, 46.0f);
		// h
		TextFrameMap['h'] = new Frame(file, 198.0f, 146.0f, 26.0f, 46.0f);
		TextSizeMap['h'] = Vector2(26.0f, 46.0f);
		// i
		TextFrameMap['i'] = new Frame(file, 225.0f, 146.0f, 12.0f, 46.0f);
		TextSizeMap['i'] = Vector2(12.0f, 46.0f);
		// j
		TextFrameMap['j'] = new Frame(file, 238.0f, 146.0f, 18.0f, 46.0f);
		TextSizeMap['j'] = Vector2(18.0f, 46.0f);
		// k
		TextFrameMap['k'] = new Frame(file, 257.0f, 146.0f, 28.0f, 46.0f);
		TextSizeMap['k'] = Vector2(28.0f, 46.0f);
		// l
		TextFrameMap['l'] = new Frame(file, 286.0f, 146.0f, 12.0f, 46.0f);
		TextSizeMap['l'] = Vector2(12.0f, 46.0f);
		// m
		TextFrameMap['m'] = new Frame(file, 299.0f, 146.0f, 42.0f, 46.0f);
		TextSizeMap['m'] = Vector2(42.0f, 46.0f);
		// n
		TextFrameMap['n'] = new Frame(file, 342.0f, 146.0f, 26.0f, 46.0f);
		TextSizeMap['n'] = Vector2(26.0f, 46.0f);
		// o
		TextFrameMap['o'] = new Frame(file, 1.0f, 194.0f, 28.0f, 46.0f);
		TextSizeMap['o'] = Vector2(28.0f, 46.0f);
		// p
		TextFrameMap['p'] = new Frame(file, 30.0f, 194.0f, 27.0f, 46.0f);
		TextSizeMap['p'] = Vector2(27.0f, 46.0f);
		// q
		TextFrameMap['q'] = new Frame(file, 58.0f, 194.0f, 28.0f, 46.0f);
		TextSizeMap['q'] = Vector2(28.0f, 46.0f);
		// r
		TextFrameMap['r'] = new Frame(file, 87.0f, 194.0f, 18.0f, 46.0f);
		TextSizeMap['r'] = Vector2(18.0f, 46.0f);
		// s
		TextFrameMap['s'] = new Frame(file, 106.0f, 194.0f, 27.0f, 46.0f);
		TextSizeMap['s'] = Vector2(27.0f, 46.0f);
		// t
		TextFrameMap['t'] = new Frame(file, 134.0f, 194.0f, 20.0f, 46.0f);
		TextSizeMap['t'] = Vector2(20.0f, 46.0f);
		// u
		TextFrameMap['u'] = new Frame(file, 155.0f, 194.0f, 26.0f, 46.0f);
		TextSizeMap['u'] = Vector2(26.0f, 46.0f);
		// v
		TextFrameMap['v'] = new Frame(file, 182.0f, 190.0f, 27.0f, 46.0f);
		TextSizeMap['v'] = Vector2(27.0f, 46.0f);
		// w
		TextFrameMap['w'] = new Frame(file, 210.0f, 194.0f, 39.0f, 46.0f);
		TextSizeMap['w'] = Vector2(39.0f, 46.0f);
		// x
		TextFrameMap['x'] = new Frame(file, 250.0f, 194.0f, 27.0f, 46.0f);
		TextSizeMap['x'] = Vector2(27.0f, 46.0f);
		// y
		TextFrameMap['y'] = new Frame(file, 278.0f, 194.0f, 26.0f, 46.0f);
		TextSizeMap['y'] = Vector2(26.0f, 46.0f);
		// z
		TextFrameMap['z'] = new Frame(file, 305.0f, 194.0f, 24.0f, 46.0f);
		TextSizeMap['z'] = Vector2(24.0f, 46.0f);
	}

	// Extra clip
	{
		// ':' // 62
		TextFrameMap[':'] = new Frame(file, 29.0f, 289.0f, 12.0f, 46.0f);
		TextSizeMap[':'] = Vector2(12.0f, 46.0f);
		// '/' // 63
		TextFrameMap['/'] = new Frame(file, 42.0f, 289.0f, 31.0f, 46.0f);
		TextSizeMap['/'] = Vector2(31.0f, 46.0f);
		// '+' //64
		TextFrameMap['+'] = new Frame(file, 77.0f, 375.0f, 30.0f, 46.0f);
		TextSizeMap['+'] = Vector2(31.0f, 46.0f);
		// '' //65
		TextFrameMap['-'] = new Frame(file, 75.0f, 290.0f, 30.0f, 46.0f);
		TextSizeMap['-'] = Vector2(18.0f, 46.0f);
		// '%' // 66
		TextFrameMap['%'] = new Frame(file, 220.0f, 287.0f, 40.0f, 46.0f);
		TextSizeMap['%'] = Vector2(40.0f, 46.0f);
		// '.' //67
		TextFrameMap['.'] = new Frame(file, 2.0f, 283.0f, 12.0f, 46.0f);
		TextSizeMap['.'] = Vector2(12.0f, 46.0f);
		// ',' // 68
		TextFrameMap[','] = new Frame(file, 15.0f, 289.0f, 13.0f, 46.0f);
		TextSizeMap[','] = Vector2(13.0f, 46.0f);
		// '!' // 69
		TextFrameMap['!'] = new Frame(file, 123.0f, 287.0f, 14.0f, 46.0f);
		TextSizeMap['!'] = Vector2(13.0f, 46.0f);
		// '<', '>' // 70 71
		TextFrameMap['<'] = new Frame(file, 330.0f, 287.0f, 29.0f, 46.0f);
		TextSizeMap['<'] = Vector2(29.0f, 46.0f);
		TextFrameMap['>'] = new Frame(file, 358.0f, 287.0f, 29.0f, 46.0f);
		TextSizeMap['>'] = Vector2(29.0f, 46.0f);
		// ''' // 72
		TextFrameMap['\''] = new Frame(file, 362.0f, 432.0f, 13.0f, 46.0f);
		TextSizeMap['\''] = Vector2(15.0f, 46.0f);
	}
}

void Text::RemoveTextInfo()
{
	for (auto& pair : TextFrameMap)
	{
		delete pair.second;
		pair.second = nullptr;
	}

	TextFrameMap.clear();
	TextSizeMap.clear();

	// 모두 제거되었으니 다시 초기화를 해야 함.
	bInit = false;
}
