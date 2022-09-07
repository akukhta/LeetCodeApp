#pragma once
#include <qsize.h>

class DefaultSizeable
{
public:
	DefaultSizeable() = default;
	QSize getDefaultSize() { return defaultSize; };
	void setDefaultSize(QSize const& size) { defaultSize = size; };
private:
	QSize defaultSize;
};