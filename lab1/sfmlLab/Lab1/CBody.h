#pragma once

class CBody
{
public:
	~CBody() {};
	virtual float GetArea() = 0;
	virtual float GetPerimeter() = 0;
};