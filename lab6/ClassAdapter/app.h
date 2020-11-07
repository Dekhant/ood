#pragma once
#include "modern_graphics_lib.h"
#include "shape_drawing_lib.h"

namespace app
{
	class CModernGraphicsAdapter : public graphics_lib::ICanvas
		, public modern_graphics_lib::CModernGraphicsRenderer
	{
	public:
		CModernGraphicsAdapter(std::ostream& strm)
			: modern_graphics_lib::CModernGraphicsRenderer(strm)
			, m_color(0, 0, 0, 1)
		{
		}

		void SetColor(uint32_t rgbColor) override
		{
			float r = float(((rgbColor >> 16) & 0xFF) / 255.0);
			float g = float((rgbColor >> 8 & 0xFF) / 255.0);
			float b = float((rgbColor & 0xFF) / 255.0);
			float a = 1.;

			m_color = { r, g, b, a };
		}

		void MoveTo(int x, int y) override
		{
			m_start = { x, y };
		}
		void LineTo(int x, int y) override
		{
			modern_graphics_lib::CPoint end(x, y);
			DrawLine(m_start, end, m_color);
		}

	private:
		modern_graphics_lib::CPoint m_start;
		modern_graphics_lib::CRGBAColor m_color;
	};

	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
	{
		using namespace shape_drawing_lib;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0xAA12B0);
		CRectangle rectangle({ 30, 40 }, 18, 24);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		CModernGraphicsAdapter canvas(std::cout);
		canvas.BeginDraw();
		shape_drawing_lib::CCanvasPainter painter(canvas);
		PaintPicture(painter);
	}
} // namespace app