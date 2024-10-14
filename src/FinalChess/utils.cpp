#include "pch.h"

namespace Utils
{
	bool pointInRect(int pX, int pY, int x, int y, int width, int height)
	{
		return (pX >= x && pX <= x + width && pY >= y && pY <= y + height);
	}
}