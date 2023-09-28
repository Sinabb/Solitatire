#include <string>
#include "Card.h"

using namespace solitaire;
using namespace Gdiplus;

Card::Card(Type type, int x, int y) : mType(type), mX(x), mY(y), mIsFront(false)
{
	mBack = std::make_unique<Image>(L"Images/bg_blank.png");

	std::wstring filename = L"Images";

	switch (mType)
	{
	case Type::Wolf:
		filename = L"Images/card_creature_wolf.png";
		break;
	case Type::Dragon:
		filename = L"Images/card_creature_dragon.png";
		break;
	case Type::Bear:
		filename = L"Images/card_creature_bear.png";
		break;
	}
	mFront = std::make_unique<Image>(filename.c_str());
}

bool Card::CheckClicked(int x, int y)
{
	return false;
}

void Card::Flip(bool isFront)
{
	mIsFront = isFront;
}

void Card::Draw(Gdiplus::Graphics& graphics)
{
	if (mIsFront)
	{
		graphics.DrawImage(mFront.get(), mX, mY, mFront->GetWidth(), mFront->GetHeight());
	}
	else
	{
		graphics.DrawImage(mBack.get(), mX, mY, mBack->GetWidth(), mBack->GetHeight());
	}
}