#define _USE_MATH_DEFINES
#include<iostream>
#include<ctime>
#include<string>
#include <SFML/Graphics.hpp>
#include<math.h>
#include"calc.h"

using namespace sf;

const float lines_num = 5;     //maximum number of divisions from 0 to the end of the axis
float scale = 10;              //default scale
bool zoom = true;              //scaling progress flag (true to draw the first frame)
float zoom_speed = 0.125;      //0 to 1 (zoom speed)
unsigned int scaling_started;  //zoom start time
unsigned int time_gone;        //time elapsed since scaling started

VideoMode vector = VideoMode::getDesktopMode(); //screen deffinition
int h = vector.height - 100, w = vector.width - 100;
VideoMode vect = VideoMode(w, h);
Event evvent;

float step = h / scale / 2.0;                 //coordinate system division length in pixels
float p = int((scale - 1) / lines_num + 1);   //mathematical coordinate system division length
int pix_step = 2;                             //distance in pixels between adjacent chart readings
int steps_num = h / pix_step;                 //total number of readings
int definition = 1000;                        //number of steps for enumeration of surface values ​​at each reading



//центр системы координат
struct centre {
public:
	double x = h / 2.0;
	double y = h / 2.0; //coordinate system center
};
centre c;

void draw_coordinate_system(RenderWindow&);
std::string str(float);
void focal_scaling(RenderWindow&, int);
std::string prepare_str(std::string);
void draw_curve(RenderWindow&);

int main()
{
	std::cout << "Write your expression like y+sin(x)=x*y\n";
	std::string s;
	std::cin >> s;



	//string formatting
	//getting a function of 2 variables
	s = prepare_str(s);

	//expression string preprocessing
	processing_expr(s);

	Vector2i mouse_pos;
	ContextSettings settings;
	settings.antialiasingLevel = 8;

	RenderWindow window(vect, "Math plot", Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	// The main loop of the application. Runs while the window is open
	while (window.isOpen())
	{
		// Processing the event queue in a loop
		while (window.pollEvent(evvent))
		{

			if (evvent.type == Event::Closed) {

				window.close();
				return 0;
			}
			if (evvent.type == Event::MouseWheelMoved) {
				focal_scaling(window, evvent.mouseWheel.delta);
				scaling_started = clock();
				zoom = true;
			}
			// Window rendering
			if (zoom) {
				draw_coordinate_system(window);

				window.display();
			}
			//maintaining the scale of objects when resizing the window
			if (evvent.type == Event::Resized)
			{
				FloatRect view(0, 0, evvent.size.width, evvent.size.height);
				window.setView(View(view));
				window.clear(Color::Black);
				h = evvent.size.height;
				w = evvent.size.width;
				draw_coordinate_system(window);
				draw_curve(window);

				window.display();
			}
		}
		time_gone = clock() - scaling_started; //мс
		if (time_gone > 100 && zoom) {
			draw_curve(window);
			zoom = false;

			window.display();
		}
	}
	return 0;
}


void draw_coordinate_system(RenderWindow& window) {
	float x_pos = c.x, y_pos = c.y;
	RectangleShape line(Vector2f(1.f, h / 2.0));
	Font font;
	font.loadFromFile("arial.ttf");
	Text text("", font, 15);
	//right lower quadrant
	//==================================
	line.setSize(Vector2f(1.f, h - c.y));
	for (float i = 0; x_pos < h; i += p) {
		line.setPosition(x_pos, c.y);
		text.setString(str(i));
		if (c.y < 0) {
			text.setPosition(x_pos + 1, 0);
		}
		else if (c.y > h) {
			text.setPosition(x_pos + 1, h - 20);
		}
		else {
			text.setPosition(x_pos + 1, c.y);
		}

		window.draw(line);
		window.draw(text);
		x_pos += step * p;
	}
	line.setSize(Vector2f(1.f, h - c.x));
	line.rotate(-90.f);
	for (float i = 0; y_pos < h; i += p) {
		line.setPosition(c.x, y_pos);
		if (i == 0) {
			text.setString(str(i));
		}
		else {
			text.setString("-" + str(i));
		}
		if (c.x < 0) {
			text.setPosition(0, y_pos + 1);
		}
		else if (c.x > h) {
			text.setPosition(h - 40, y_pos + 1);
		}
		else {
			text.setPosition(c.x, y_pos + 1);
		}
		window.draw(line);
		window.draw(text);
		y_pos += step * p;
	}
	//upper left quadrant
	//==================================
	x_pos = c.x, y_pos = c.y;
	line.setSize(Vector2f(1.f, c.y));
	line.rotate(-90.f);
	for (float i = 0; x_pos > 0; i += p) {
		line.setPosition(x_pos, c.y);
		if (i == 0) {
			text.setString(str(i));
		}
		else {
			text.setString("-" + str(i));
		}
		if (c.y > h) {
			text.setPosition(x_pos + 1, h - 20);
		}
		else if (c.y < 0) {
			text.setPosition(x_pos + 1, 0);
		}
		else {
			text.setPosition(x_pos + 1, c.y);
		}
		window.draw(line);
		window.draw(text);
		x_pos -= step * p;
	}
	line.setSize(Vector2f(1.f, c.x));
	line.rotate(-90.f);
	for (float i = 0; y_pos > 0; i += p) {
		line.setPosition(c.x, y_pos);
		text.setString(str(i));
		if (c.x > h) {
			text.setPosition(h - 20, y_pos + 1);
		}
		else if (c.x < 0) {
			text.setPosition(0, y_pos + 1);
		}
		else {
			text.setPosition(c.x, y_pos + 1);
		}
		window.draw(line);
		window.draw(text);
		y_pos -= step * p;
	}
	//lower left quadrant
	//==================================
	x_pos = c.x, y_pos = c.y;
	line.setSize(Vector2f(1.f, h - c.y));
	line.rotate(-90.f);
	for (float i = 0; x_pos > 0; i += p) {
		line.setPosition(x_pos, c.y);
		window.draw(line);
		x_pos -= step * p;
	}
	line.setSize(Vector2f(1.f, c.x));
	line.rotate(-90.f);
	for (float i = 0; y_pos < h; i += p) {
		line.setPosition(0.0, y_pos);
		window.draw(line);
		y_pos += step * p;
	}
	//right upper quadrant
	//==================================
	x_pos = c.x, y_pos = c.y;
	line.setSize(Vector2f(1.f, c.y));
	line.rotate(-90.f);
	for (float i = 0; x_pos < h; i += p) {
		line.setPosition(x_pos, c.y);
		window.draw(line);
		x_pos += step * p;
	}
	line.rotate(-90.f);
	line.setSize(Vector2f(1.f, h - c.x));
	for (float i = 0; y_pos > 0; i += p) {
		line.setPosition(h, y_pos);
		window.draw(line);
		y_pos -= step * p;
	}
	//maintaining borders
	//==================================
	if (c.x > h) {
		RectangleShape r(Vector2f(h, h));
		r.setFillColor(Color(0, 0, 0));
		r.setPosition(h, 0.0);
		window.draw(r);
	}
}


std::string str(float n) {
	std::string s = std::to_string(n);
	int i = s.length() - 1;
	while (true) {
		if (s[i] != '0') {
			if (s[i] == '.') {
				s.erase(i);
			}
			else {
				s.erase(i + 1);
			}
			break;
		}
		i--;
	}
	return s;
}



void focal_scaling(RenderWindow& window, int delta) {
	window.clear();
	Vector2i mouse_pos = Mouse::getPosition(window);
	float math_rx = (mouse_pos.x - c.x) / (step);
	float math_ry = (c.y - mouse_pos.y) / (step);
	if (delta == -1) {
		scale += scale * zoom_speed;

		step = h / scale / 2.0;
		p = int((scale - 1) / lines_num + 1);
		if (scale <= lines_num / 2) {
			p = 1 / float(int(lines_num / scale));
		}
		c.x = mouse_pos.x - math_rx * step;
		c.y = mouse_pos.y + math_ry * step;
	}
	else if (delta == 1) {
		scale -= scale * zoom_speed;

		step = h / scale / 2.0;
		p = int((scale - 1) / lines_num + 1);
		if (scale <= lines_num / 2) {
			p = 1 / float(int(lines_num / scale));
		}
		c.x = mouse_pos.x - math_rx * step;
		c.y = mouse_pos.y + math_ry * step;

	}
}


std::string prepare_str(std::string s) {
	int i = 0;
	while (s[i] != '=') {
		i++;
	}
	std::string b = s;
	std::string l_s = s.erase(0, i + 1);
	std::string r_s = b.erase(i);
	bool f = false;
	if (l_s[0] != '-') {
		l_s = "-" + l_s;
		f = true;
	}
	std::vector<int> br;
	char* symb = &l_s[0];
	while (*symb != '\0') {
		if (*symb == '(') {
			br.push_back(1);
		}
		else if (*symb == ')') {
			br.pop_back();
		}
		else if (*symb == '+' && br.size() == 0) {
			*symb = '-';
		}
		else if (*symb == '-' && br.size() == 0) {
			if (f) {
				f = false;
			}
			else {
				*symb = '+';
			}
		}
		symb++;
	}
	return r_s + l_s;
}


void draw_curve(RenderWindow& window) {

	float step = h / scale / 2.0;                 //coordinate system division length in pixels
	float p = int((scale - 1) / lines_num + 1);   //mathematical coordinate system division length
	int pix_step = 2;                             //distance in pixels between adjacent chart readings
	int steps_num = h / pix_step;                 //total number of readings

	std::vector<float> points(definition);               //array of values ​​of one sample 
	std::vector<std::vector<float>> sections(steps_num + 1); //array of all readings

	//readout array initialization
	for (int i = 0; i < definition; i++) {
		points[i] = 0.0;
	}
	for (int i = 0; i < steps_num + 1; i++) {
		sections[i] = points;
	}

	//definition of construction boundaries
	//math coordinates

	float x_begin = (0 - c.x) / (step);
	float y_begin = (c.y - h) / (step);
	float x_end = (h - c.x) / (step);
	float y_end = (c.y - 0) / (step);

	//drawing horizontally

	double x, y, i, j, Fxy, pr_Fxy = 0, pr_pr_Fxy, pr_x = 0, pr_y = h, r = 0, angle = 0;
	float x_step = (x_end - x_begin) / float(steps_num);
	float y_step = (y_end - y_begin) / float(definition);

	float* point, * pr_point;

	for (i = 0, x = x_begin; i < steps_num; i++, x += x_step) {
		point = &sections[i][0];
		y = y_begin;
		set_x(x);
		set_y(y);
		Fxy = calculate();
		for (y = y_begin; y < y_end;) {
			if (Fxy <= 0) {
				y += y_step;
				set_y(y);
				pr_pr_Fxy = pr_Fxy;
				pr_Fxy = Fxy;
				Fxy = calculate();
				if (Fxy > 0) {
					if (pr_Fxy - pr_pr_Fxy > 0) {
						*point = c.y - y * step;
						point++;
					}
				}
			}
			else if (Fxy > 0) {
				y += y_step;
				set_y(y);
				pr_pr_Fxy = pr_Fxy;
				pr_Fxy = Fxy;
				Fxy = calculate();
				if (Fxy < 0) {
					if (pr_Fxy - pr_pr_Fxy < 0) {
						*point = c.y - y * step;
						point++;
					}
				}
			}
			else {
				y += y_step;
				set_y(y);
				Fxy = calculate();
				*point = INFINITY;
				point++;
			}
		}
	}

	RectangleShape line(Vector2f(1.0, 1.0));
	float th = 4;//line thickness
	line.setOrigin(0.0, th / 2);
	line.setFillColor(Color(255, 0, 0));
	for (i = 1; pr_x < h - pix_step; i++, pr_x += pix_step) {
		point = &sections[i][0];
		pr_point = &sections[i - 1][0];
		for (j = 0; *point != 0.0 && *pr_point != 0.0; j++, point++, pr_point++) {
			if (*point != INFINITY && *pr_point != INFINITY) {
				r = sqrt(float(pix_step * pix_step) + (*pr_point - *point) * (*pr_point - *point));
				angle = -atan((*pr_point - *point) / float(pix_step)) / M_PI * 180;
				if (abs(angle) < 50) {
					line.setSize(Vector2f(r, th));
					line.setPosition(pr_x, *pr_point);
					line.rotate(angle);
					window.draw(line);
					line.rotate(-angle);
				}
			}
		}
	}

	for (i = 0; i < steps_num; i++) {
		point = &sections[i][0];
		for (j = 0; j < definition; j++, point++) {
			*point = 0.0;
		}
	}

	//vertical drawing

	x_step = (x_end - x_begin) / float(definition);
	y_step = (y_end - y_begin) / float(steps_num);


	for (i = 0, y = y_begin; i < steps_num; i++, y += y_step) {
		point = &sections[i][0];
		x = x_begin;
		set_x(x);
		set_y(y);
		Fxy = calculate();
		for (x = x_begin; x < x_end;) {
			if (Fxy <= 0) {
				x += x_step;
				set_x(x);
				pr_pr_Fxy = pr_Fxy;
				pr_Fxy = Fxy;
				Fxy = calculate();
				if (Fxy > 0) {
					if (pr_Fxy - pr_pr_Fxy > 0) {
						*point = c.x + x * step;
						point++;
					}
				}
			}
			else if (Fxy > 0) {
				x += x_step;
				set_x(x);
				pr_pr_Fxy = pr_Fxy;
				pr_Fxy = Fxy;
				Fxy = calculate();
				if (Fxy < 0) {
					if (pr_Fxy - pr_pr_Fxy < 0) {
						*point = c.x + x * step;
						point++;
					}
				}
			}
			else {
				x += x_step;
				set_x(x);
				Fxy = calculate();
				*point = INFINITY;
				point++;
			}
		}
	}

	line.rotate(-90.0);
	for (i = 1; pr_y > pix_step; i++, pr_y -= pix_step) {
		point = &sections[i][0];
		pr_point = &sections[i - 1][0];
		for (j = 0; *point != 0.0 && *pr_point != 0.0; j++, point++, pr_point++) {
			if (*point != INFINITY && *pr_point != INFINITY) {
				r = sqrt(float(pix_step * pix_step) + (*pr_point - *point) * (*pr_point - *point));
				angle = -atan((*pr_point - *point) / float(pix_step)) / M_PI * 180;
				if (abs(angle) < 50) {
					line.setSize(Vector2f(r, th));
					line.setPosition(*pr_point, pr_y);
					line.rotate(angle);
					window.draw(line);
					line.rotate(-angle);
				}
			}
		}
	}

	for (i = 0; i < steps_num; i++) {
		point = &sections[i][0];
		for (j = 0; j < definition; j++, point++) {
			*point = 0.0;
		}
	}

}
