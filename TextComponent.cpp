#pragma region Include Statements
#include "TextComponent.h"
#pragma endregion

TextComponent::TextComponent(void)
{

}

TextComponent::~TextComponent(void)
{

}

bool TextComponent::Init(DWORD size, LPDIRECT3DDEVICE9 device)
{
	// Used to initialise and create a new font
	D3DXCreateFont(device, size, 0, FW_NORMAL, 1, false, DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		"Arial", &g_font);

	return true;
}

void TextComponent::DrawString(std::string text, int x, int y, int width, int height)
{
	RECT rect = {0, 0, width, height};

	// Set the destination of the text on screen
	SetRect(&rect, x, y, width, height);

	// Draw the text
	g_font->DrawTextA(NULL, text.c_str(), -1, &rect, DT_LEFT | DT_NOCLIP, 
		0xFFFFFFFF);
}