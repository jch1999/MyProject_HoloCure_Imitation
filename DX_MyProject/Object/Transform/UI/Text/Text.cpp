#include "framework.h"

Text::Text()
{
	wstring file = L"Textures/Text/PC Computer - LEGO Star Wars The Complete Saga - Font.png";
	vector<Frame*> frames;
	
	// number clip
	for (int i = 0; i < 10; i++)//0~9
	{
		frames.push_back(new Frame(file, i * 32.0f, 242.0f, 32.0f, 40.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}
	// Capital clip // 10 ~35
	{
		// A
		frames.push_back(new Frame(file, 2.0f, 3.0f, 35.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// B
		frames.push_back(new Frame(file, 39.0f, 3.0f, 31.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// C
		frames.push_back(new Frame(file, 73.0f, 2.0f, 32.0f, 40.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// D
		frames.push_back(new Frame(file, 112.0f, 3.0f, 33.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// E
		frames.push_back(new Frame(file, 153.0f, 3.0f, 28.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// F
		frames.push_back(new Frame(file, 188.0f, 3.0f, 27.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// G
		frames.push_back(new Frame(file, 220.0f, 2.0f, 33.0f, 40.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// H
		frames.push_back(new Frame(file, 262.0f, 3.0f, 31.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}
	{
		// I
		frames.push_back(new Frame(file, 303.0f, 3.0f, 13.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// J
		frames.push_back(new Frame(file, 322.0f, 3.0f, 21.0f, 39.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// K
		frames.push_back(new Frame(file, 353.0f, 3.0f, 32.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// L
		frames.push_back(new Frame(file, 392.0f, 3.0f, 27.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// M
		frames.push_back(new Frame(file, 3.0f, 51.0f, 38.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// N
		frames.push_back(new Frame(file, 44.0f, 51.0f, 31.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// O
		frames.push_back(new Frame(file, 78.0f, 50.0f, 35.0f, 40.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// P
		frames.push_back(new Frame(file, 116.0f, 51.0f, 31.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}
	{
		// Q
		frames.push_back(new Frame(file, 153.0f, 50.0f, 35.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// R
		frames.push_back(new Frame(file, 195.0f, 51.0f, 32.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// S
		frames.push_back(new Frame(file, 233.0f, 50.0f, 32.0f, 40.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// T
		frames.push_back(new Frame(file, 270.0f, 51.0f, 30.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// U
		frames.push_back(new Frame(file, 305.0f, 51.0f, 29.0f, 39.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// V
		frames.push_back(new Frame(file, 341.0f, 51.0f, 32.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// W
		frames.push_back(new Frame(file, 375.0f, 51.0f, 48.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// X
		frames.push_back(new Frame(file, 10.0f,99.0f, 33.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// Y
		frames.push_back(new Frame(file, 46.0f, 99.0f, 34.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// Z
		frames.push_back(new Frame(file, 83.0f, 99.0f, 30.0f, 38.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}
	// small clip // 36 ~61
	{
		// a
		frames.push_back(new Frame(file, 1.0f, 146.0f, 29.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// b
		frames.push_back(new Frame(file, 31.0f, 146.0f, 27.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// c
		frames.push_back(new Frame(file, 59.0f, 146.0f, 26.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// d
		frames.push_back(new Frame(file, 87.0f, 146.0f, 27.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// e
		frames.push_back(new Frame(file, 116.0f, 146.0f, 28.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// f
		frames.push_back(new Frame(file, 145.0f, 146.0f, 21.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// g
		frames.push_back(new Frame(file, 167.0f, 146.0f, 30.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// h
		frames.push_back(new Frame(file, 198.0f, 146.0f, 26.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}
	{
		// i
		frames.push_back(new Frame(file, 225.0f, 146.0f, 12.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// j
		frames.push_back(new Frame(file, 238.0f, 146.0f, 18.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// k
		frames.push_back(new Frame(file, 257.0f, 146.0f, 28.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// l
		frames.push_back(new Frame(file, 286.0f, 146.0f, 12.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// m
		frames.push_back(new Frame(file, 299.0f, 146.0f, 42.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// n
		frames.push_back(new Frame(file, 342.0f, 146.0f, 26.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// o
		frames.push_back(new Frame(file, 1.0f, 194.0f, 28.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// p
		frames.push_back(new Frame(file, 30.0f, 194.0f, 27.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}
	{
		// q
		frames.push_back(new Frame(file, 58.0f, 194.0f, 28.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// r
		frames.push_back(new Frame(file, 87.0f, 194.0f, 18.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// s
		frames.push_back(new Frame(file, 106.0f, 194.0f, 27.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// t
		frames.push_back(new Frame(file, 134.0f, 194.0f, 20.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// u
		frames.push_back(new Frame(file, 155.0f, 194.0f, 26.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// v
		frames.push_back(new Frame(file, 182.0f, 190.0f, 27.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// w
		frames.push_back(new Frame(file, 210.0f, 194.0f, 39.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// x
		frames.push_back(new Frame(file, 250.0f, 194.0f, 27.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// y
		frames.push_back(new Frame(file, 278.0f, 194.0f, 26.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
		// z
		frames.push_back(new Frame(file, 305.0f, 194.0f, 24.0f, 46.0f));
		clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
		frames.clear();
	}

	// Extra clip
	// ':' // 62
	frames.push_back(new Frame(file, 29.0f, 289.0f, 12.0f, 46.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// '/' // 63
	frames.push_back(new Frame(file, 42.0f, 289.0f, 31.0f, 46.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// '+' //64
	frames.push_back(new Frame(file, 77.0f, 375.0f, 30.0f, 46.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// '%' // 65
	frames.push_back(new Frame(file, 220.0f, 287.0f, 40.0f, 46.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// '.' //66
	frames.push_back(new Frame(file, 2.0f, 283.0f, 12.0f, 46.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// ',' // 67
	frames.push_back(new Frame(file, 15.0f, 289.0f, 13.0f, 46.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// '!' // 68
	frames.push_back(new Frame(file, 123.0f, 287.0f, 14.0f, 46.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	// '<', '>' // 69 70
	frames.push_back(new Frame(file, 330.0f, 287.0f, 29.0f, 46.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();
	frames.push_back(new Frame(file, 358.0f, 287.0f, 29.0f, 46.0f));
	clips.push_back(new Clip(frames, Clip::CLIP_TYPE::LOOP, 1.0f / 1.0f));
	frames.clear();

	id = UI_ID::LEVEL_TEXT;
	type = UI_TYPE::TEXT;
	SetText('0');
	ui_scale = Vector2(1, 1);
	offset = Vector2(0, 0);
	is_active = false;
}

Text::~Text()
{
}

void Text::SetClipIdx(int idx)
{
	clip_idx = idx;
}

void Text::SetText(char c)
{
	this->c = c;
	switch (c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		clip_idx = (int)(c - '0');
	}
		break;
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
	{
		clip_idx = 10 + (int)(c - 'A');
	}
		break;
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
		clip_idx = 36 + (int)(c - 'a');
		break;
	case ':':
		clip_idx = 62;
		break;
	case '/':
		clip_idx = 63;
		break;
	case '+':
		clip_idx = 64;
		break;
	case '%':
		clip_idx = 65;
		break;
	case '.':
		clip_idx = 66;
		break;
	case ',':
		clip_idx = 67;
		break;
	case '!':
		clip_idx = 68;
		break;
	case '<':
		clip_idx = 69;
		break;
	case '>':
		clip_idx = 70;
		break;
	default:
		break;
	}
	SetSize(c);
}

void Text::SetSize(char c)
{
	switch (c)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		ui_size = Vector2(32.0f, 40.0f);
		break;
	case 'A':
		ui_size = Vector2(35.0f, 38.0f);
		break;
	case 'B':
		ui_size = Vector2(31.0f, 38.0f);
		break;
	case 'C':
		ui_size = Vector2(32.0f, 40.0f);
		break;
	case 'D':
		ui_size = Vector2(33.0f, 38.0f);
		break;
	case 'E':
		ui_size = Vector2(28.0f, 38.0f);
		break;
	case 'F':
		ui_size = Vector2(27.0f, 38.0f);
		break;
	case 'G':
		ui_size = Vector2(33.0f, 40.0f);
		break;
	case 'H':
		ui_size = Vector2(31.0f, 38.0f);
		break;
	case 'I':
		ui_size = Vector2(13.0f, 38.0f);
		break;
	case 'J':
		ui_size = Vector2(21.0f, 39.0f);
		break;
	case 'K':
		ui_size = Vector2(32.0f, 38.0f);
		break;
	case 'L':
		ui_size = Vector2(27.0f, 38.0f);
		break;
	case 'M':
		ui_size = Vector2(38.0f, 38.0f);
		break;
	case 'N':
		ui_size = Vector2(31.0f, 38.0f);
		break;
	case 'O':
		ui_size = Vector2(35.0f, 40.0f);
		break;
	case 'P':
		ui_size = Vector2(31.0f, 38.0f);
		break;
	case 'Q':
		ui_size = Vector2(35.0f, 46.0f);
		break;
	case 'R':
		ui_size = Vector2(32.0f, 38.0f);
		break;
	case 'S':
		ui_size = Vector2(32.0f, 40.0f);
		break;
	case 'T':
		ui_size = Vector2(30.0f, 38.0f);
		break;
	case 'U':
		ui_size = Vector2(29.0f, 39.0f);
		break;
	case 'V':
		ui_size = Vector2(32.0f, 38.0f);
		break;
	case 'W':
		ui_size = Vector2(48.0f, 38.0f);
		break;
	case 'X':
		ui_size = Vector2(33.0f, 38.0f);
		break;
	case 'Y':
		ui_size = Vector2(34.0f, 38.0f);
		break;
	case 'Z':
		ui_size = Vector2(30.0f, 38.0f);
		break;
	case 'a':
		ui_size = Vector2(29.0f, 46.0f);
		break;
	case 'b':
		ui_size = Vector2(27.0f, 46.0f);
		break;
	case 'c':
		ui_size = Vector2(26.0f, 46.0f);
		break;
	case 'd':
		ui_size = Vector2(27.0f, 46.0f);
		break;
	case 'e':
		ui_size = Vector2(28.0f, 46.0f);
		break;
	case 'f':
		ui_size = Vector2(21.0f, 46.0f);
		break;
	case 'g':
		ui_size = Vector2(30.0f, 46.0f);
		break;
	case 'h':
		ui_size = Vector2(26.0f, 46.0f);
		break;
	case 'i':
		ui_size = Vector2(12.0f, 46.0f);
		break;
	case 'j':
		ui_size = Vector2(18.0f, 46.0f);
		break;
	case 'k':
		ui_size = Vector2(28.0f, 46.0f);
		break;
	case 'l':
		ui_size = Vector2(12.0f, 46.0f);
		break;
	case 'm':
		ui_size = Vector2(42.0f, 46.0f);
		break;
	case 'n':
		ui_size = Vector2(26.0f, 46.0f);
		break;
	case 'o':
		ui_size = Vector2(28.0f, 46.0f);
		break;
	case 'p':
		ui_size = Vector2(27.0f, 46.0f);
		break;
	case 'q':
		ui_size = Vector2(28.0f, 46.0f);
		break;
	case 'r':
		ui_size = Vector2(18.0f, 46.0f);
		break;
	case 's':
		ui_size = Vector2(27.0f, 46.0f);
		break;
	case 't':
		ui_size = Vector2(20.0f, 46.0f);
		break;
	case 'u':
		ui_size = Vector2(26.0f, 46.0f);
		break;
	case 'v':
		ui_size = Vector2(27.0f, 46.0f);
		break;
	case 'w':
		ui_size = Vector2(39.0f, 46.0f);
		break;
	case 'x':
		ui_size = Vector2(27.0f, 46.0f);
		break;
	case 'y':
		ui_size = Vector2(26.0f, 46.0f);
		break;
	case 'z':
		ui_size = Vector2(24.0f, 46.0f);
		break;
	case ':':
		ui_size = Vector2(12.0f, 46.0f);
		break;
	case '/':
		ui_size = Vector2(31.0f, 46.0f);
		break;
	case '+':
		ui_size = Vector2(31.0f, 46.0f);
		break;
	case '%':
		ui_size = Vector2(40.0f, 46.0f);
		break;
	case '.':
		ui_size = Vector2(12.0f, 46.0f);
		break;
	case ',':
		ui_size = Vector2(13.0f, 46.0f);
		break;
	case '!':
		ui_size = Vector2(13.0f, 46.0f);
		break;
	case '<':
		ui_size = Vector2(29.0f, 46.0f);
		break;
	case '>':
		ui_size = Vector2(29.0f, 46.0f);
		break;
	default:
		break;
	}
}

void Text::Update()
{
	if (!is_active)return;

	scale = clips[clip_idx]->GetFrameSize() * ui_size / clips[clip_idx]->GetFrameOriginSize() * ui_scale;
	clips[clip_idx]->Update();

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

	clips[clip_idx]->Render();
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
