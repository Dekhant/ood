#pragma once
#include <string>
#include <memory>

class IImage
{
public:
	virtual std::string GetPath()const = 0;

	virtual int GetWidth()const = 0;

	virtual int GetHeight()const = 0;

	virtual void Resize(int width, int height) = 0;

	virtual ~IImage() = default;
};

typedef std::shared_ptr<IImage> IImagePtr;
typedef std::shared_ptr<const IImage> IImageConstPtr;