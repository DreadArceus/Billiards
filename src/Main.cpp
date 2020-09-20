#include <vector>
#include <cmath>

using namespace std;
using namespace sf;

int main()
{
	RectangleShape pixel;
	pixel.setSize(Vector2f(1, 1));

	RenderWindow rw(VideoMode(1200, 600), "Billiards");
	while(rw.isOpen())
	{
		Event event;
		while(rw.pollEvent(event))
		{
			if(event.type == Event::Closed)
			{
				rw.close();
			}
		}
		//background green
		rw.clear(Color(50, 150, 50));

		//wood borders
		pixel.setFillColor(Color(110, 42, 42));
		static constexpr int woodWidth = 25;
		for(int i = 0; i < rw.getSize().x; i++)
		{
			for(int j = 0; j < woodWidth; j++)
			{
				pixel.setPosition(i, j);
				rw.draw(pixel);
				pixel.setPosition(i, rw.getSize().y - j);
				rw.draw(pixel);
				pixel.setPosition(j, i);
				rw.draw(pixel);
				pixel.setPosition(rw.getSize().x - j, i);
				rw.draw(pixel);
			}
		}
		//Inner Borders
		pixel.setFillColor(Color(11, 102, 35));
		static constexpr int cushionWidth = 15, buffer = 25;
		for(int i = woodWidth + cushionWidth + buffer; i < (int)rw.getSize().x - (woodWidth + cushionWidth + buffer); i++)
		{
			for(int j = woodWidth; j < woodWidth + cushionWidth; j++)
			{
				pixel.setPosition(i, j);
				rw.draw(pixel);
				pixel.setPosition(i, rw.getSize().y - j);
				rw.draw(pixel);
			}
		}
		for(int j = woodWidth + cushionWidth + buffer; j < (int)rw.getSize().y - (woodWidth + cushionWidth + buffer); j++)
		{
			for(int i = woodWidth; i < woodWidth + cushionWidth; i++)
			{
				pixel.setPosition(i, j);
				rw.draw(pixel);
				pixel.setPosition(rw.getSize().x - i, j);
				rw.draw(pixel);
			}
		}
		//corner holes
		pixel.setFillColor(Color::Black);
		static constexpr int holeRadius = 20, holeCentrePosition = 30;
		for(int i = 0; i < rw.getSize().x; i++)
		{
			for(int j = 0; j < rw.getSize().y; j++)
			{
				if(pow(i - holeCentrePosition, 2) + pow(j - holeCentrePosition, 2) <= pow(holeRadius, 2)
				|| pow(i - (int)rw.getSize().x + holeCentrePosition, 2) + pow(j - holeCentrePosition, 2) <= pow(holeRadius, 2)
				|| pow(i - holeCentrePosition, 2) + pow(j - (int)rw.getSize().y + holeCentrePosition, 2) <= pow(holeRadius, 2)
				|| pow((int)rw.getSize().x - holeCentrePosition - i, 2) + pow((int)rw.getSize().y - holeCentrePosition - j, 2) <= pow(holeRadius, 2)
				|| pow(i - (int)rw.getSize().x / 2, 2) + pow(j - holeCentrePosition, 2) <= pow(holeRadius, 2)
				|| pow(i - (int)rw.getSize().x / 2, 2) + pow(j - (int)rw.getSize().y + holeCentrePosition, 2) <= pow(holeRadius, 2))
				{
					pixel.setPosition(i, j);
					rw.draw(pixel);
				}
			}
		}
		//helpers
		pixel.setFillColor(Color(11, 102, 35));
		static constexpr double slope1 = 1, slope2 = -1;
		int x1 = woodWidth + cushionWidth, x2 = woodWidth + cushionWidth + buffer, x3 = rw.getSize().x - x2, x4 = rw.getSize().x - x1;
		int y1 = woodWidth + cushionWidth, y2 = woodWidth + cushionWidth + buffer, y3 = rw.getSize().y - y2, y4 = rw.getSize().y - y1;
		for(int i = 0; i < rw.getSize().x; i++)
		{
			for(int j = 0; j < rw.getSize().y; j++)
			{
				if(	(i >= woodWidth && i < x1 && j < y2 && (j-y2) >= slope1 * (i - x1))
				||	(i >= woodWidth && i < x1 && j >= y3 && (j-y3) <= slope2 * (i - x1))
				||	(i <= rw.getSize().x - woodWidth && i >= x4 && j < y2 && (j-y2) >= slope2 * (i-x4))
				||	(i <= rw.getSize().x - woodWidth && i >= x4 && j >= y3 && (j-y3) <= slope1 * (i-x4))
				||	(j >= woodWidth && j < y1 && i < x2 && (j-y1) <= slope1 *(i-x2))
				||	(j >= woodWidth && j < y1 && i >= x3 && (j-y1) <= slope2 * (i-x3))
				||	(j <= rw.getSize().y - woodWidth && j >= y4 && i < x2 && (j-y4) >= slope2 * (i-x2))
				||	(j <= rw.getSize().y - woodWidth && j >= y4 && i >= x3 && (j-y4) >= slope1 * (i-x3)))
				{
					pixel.setPosition(i, j);
					rw.draw(pixel);
				}
			}
		}

		rw.display();
	}
}