#pragma warning(disable:4326)

#include<Windows.h>
#include<iostream>
using namespace std;

/*
------------------------------------------------------
enum (enumeration - перечисление) - это набор именованных констант типа int.
------------------------------------------------------
*/

//Создаем тип данных Color
namespace Geometry
{
	enum Color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,

		some_colore,
		console_blue = 0x99,
		console_green = 0xAA,
		console_red = 0xCC,
		console_default = 0x07
	};

	class Shape
	{
	protected:
		unsigned int start_x;
		unsigned int start_y;
		unsigned int line_width;
		Color color;
	public:
		void set_start_x(unsigned int start_x)
		{
			if (start_x > 300)start_x = 300;
			this->start_x = start_x;
		}
		void set_start_y(unsigned int start_y)
		{
			if (start_y > 300)start_y = 300;
			this->start_y = start_y;
		}
		void set_line_width(unsigned int line_width)
		{
			if (line_width > 20)line_width = 20;
			this->line_width = line_width;
		}
		Shape(Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width) :
			color(color)
		{
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		virtual ~Shape() {}

		virtual double get_area()const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const = 0;
	};

	class Square :public Shape
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		const double& set_side(double side)
		{
			if (side <= 0)side = 10;
			this->side = side;
			return this->side;
		}
		Square(
			double side,
			Color color,
			unsigned int start_x, unsigned int start_y,
			unsigned int line_width)
			:Shape(color, start_x, start_y, line_width)/*,side(set_side(side))*/
		{
			set_side(side);
		}
		~Square() {}

		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			//H - Handle
			HWND hConsole = GetConsoleWindow();	//Получаем окно консоли, чтобы к нему можно было обратиться
			HDC hdc = GetDC(hConsole);//Создаем контекст устройства для полученного окна.
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);//Создаем карандаш, который будет рисовать контур
			//PS_SOLID - сплошная линия, 5 - толщина линии 5 пикселов, RGB(...) - цвет.
			SelectObject(hdc, hPen);//Выбираем созданный карандаш, чтобы им можно было рисовать.
			HBRUSH hBrush = CreateSolidBrush(color);//Создаем кисть. Кисть закрашивает замкнутые фигуры.
			SelectObject(hdc, hBrush);//Выбираем созданную кисть.
			//Кисть и карандаш выбираются для того, чтобы функция Rectangle понимала чем рисовать

			::Rectangle(hdc, start_x, start_y, start_x + side, start_y + side);//Рисует квадрат

			//Удаляем созданную кисть и карандаш:
			DeleteObject(hBrush);
			DeleteObject(hPen);
			//Освобождаем контекст устройства:
			ReleaseDC(hConsole, hdc);
		}
		void info()const
		{
			cout << "Квадрат:\n"
				<< "Длина:	  " << side << endl
				<< "Площадь:  " << get_area() << endl 
				<< "Периметр: " << get_perimeter() << endl;
			draw();
			cout << endl;

		}
	};

	class Rectangle :public Shape
	{
		double length;
		double width;
	public:
		double get_length()const
		{
			return length;
		}
		double get_width()const
		{
			return width;
		}
		void set_length(double length)
		{
			if (length <= 0)length = 1;
			this->length = length;
		}
		void set_width(double width)
		{
			if (width <= 0)width = 1;
			this->width = width;
		}
		Rectangle(Color color, double length, double width,
			unsigned int start_x, unsigned int start_y, unsigned int line_width)
			:Shape(color, start_x, start_y, line_width)
		{
			set_length(length);
			set_width(width);
		}
		~Rectangle() {}

		double get_area()const
		{
			return length * width;
		}
		double get_perimeter()const
		{
			return (length + width) * 2;
		}
		void draw()const
		{
			HWND hConsole = GetConsoleWindow();
			HDC hdc = GetDC(hConsole);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			SelectObject(hdc, hPen);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hBrush);

			::Rectangle(hdc, start_x, start_y, start_x + length, start_y + width);

			DeleteObject(hBrush);
			DeleteObject(hPen);
			ReleaseDC(hConsole, hdc);
		}

		void info()const
		{
			cout << "Прямоугольник:\n"
				<< "Длина:	  " << length << endl
				<< "Ширина:   " << width << endl
				<< "Площадь:  " << get_area() << endl 
				<< "Периметр: " << get_perimeter() << endl;
			draw();
			cout << endl;

		}
	};

	class Triangle :public Shape
	{
	public:
		Triangle(Color color, unsigned int start_x, unsigned int start_y, unsigned int line_width) :Shape(color, start_x, start_y, line_width) {}
		~Triangle() {}

		virtual double get_height()const = 0;
	};
	class EquilateralTriangle :public Triangle
	{
		double side;
	public:
		double get_side()const
		{
			return side;
		}
		double set_side(double side)
		{
			if (side <= 0)side = 1;
			this->side = side;
			return this->side;
		}
		EquilateralTriangle(Color color, double side,
			unsigned int start_x, unsigned int start_y, unsigned int line_width)
			:Triangle(color, start_x, start_y, line_width)
		{
			set_side(side);
		}
		~EquilateralTriangle() {}
		double get_height()const
		{
			return sqrt(3) / 2 * side;
		}
		double get_area()const
		{
			return get_height() * side / 2;
		}
		double get_perimeter()const
		{
			return side * 3;
		}
		void draw()const
		{
			HWND hwnd = GetDesktopWindow();
			hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT point[] =
			{
				{start_x, start_y + side},
				{start_x + side, start_y + side},
				{start_x + side / 2, start_y + side - get_height()}
			};

			Polygon(hdc, point, sizeof(point) / sizeof(POINT));

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << "Треугольник:\n" 
				<< "Длина:    " << side << endl 
				<< "Площадь:  " << get_area() << endl 
				<< "Периметр: " << get_perimeter() << endl 
				<< "Высота:   " << get_height() << endl;
			draw();
			cout << endl;
		}
	};
}

void main()
{
	
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD buffer = { 16,16 };
	//SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, &buffer);
	setlocale(LC_ALL, "");
	//Shape shape(Color::console_blue);
	Geometry::Square square(250, Geometry::Color::green, 100, 200, 5);
	Geometry::Rectangle rec(Geometry::Color::red, 400, 200, 300, 400, 5);
	Geometry::EquilateralTriangle tri(Geometry::Color::blue, 250, 700, 700, 5);
	square.info();
	rec.info();
	tri.info();

}