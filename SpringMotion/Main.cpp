#include "Platform/Platform.hpp"
#include "wtypes.h"
#include <iostream>

int horizontal, vertical, fps;

float current_time, machine_time, prec;
float damping_constant, spring_constant, spring_mass;

class Spring
{
private:
	float x, v, a;

public:
	void setX(float init_x)
	{
		x = init_x;
	}
	void setV(float init_v)
	{
		v = init_v;
	}
	void setA(float init_a)
	{
		a = init_a;
	}
	void operate(float time_interval)
	{
		v = v + (a * time_interval);
		x = x + (v * time_interval);
	}
	float getX()
	{
		return x;
	}
	float getV()
	{
		return v;
	}
	float getA()
	{
		return a;
	}
};

Spring spring;

void delay(float n_seconds);
void getDesktopResolution(int& horizontal, int& vertical);
void simulationLoop();

void simulationLoop()
{
	float scaling_factor = (horizontal / 2 - 50) / (1.25 * spring.getX());

	sf::RectangleShape spring_rect;
	spring_rect.setFillColor(sf::Color::White);

	sf::Texture spring_texture;
	spring_texture.loadFromFile("data/spring_texture.png");

	sf::Font font;
	font.loadFromFile("data/futura.ttf");

	sf::Text heading;
	heading.setFont(font);
	heading.setString("Spring Motion Simulation");
	heading.setPosition(horizontal / 2 - 155, 10);
	heading.setStyle(sf::Text::Bold);

	sf::Text params;
	params.setFont(font);
	params.setPosition(horizontal / 2 - 550, vertical / 2 + 300);
	params.setStyle(sf::Text::Bold);

	sf::RenderWindow window(sf::VideoMode(horizontal, vertical), "Spring Motion Simulation", sf::Style::Fullscreen);
	window.setFramerateLimit(fps);
	window.requestFocus();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape)
				{
					window.close();
				}
			}
		}

		window.clear(sf::Color::Black);

		while (current_time < machine_time)
		{
			spring.setA(spring_constant * spring.getX() + damping_constant * spring.getV());
			spring.operate(prec);
			printf("%f %f %f %f %f\n", current_time, machine_time, spring.getX(), spring.getV(), spring.getA());
			current_time = current_time + prec;
		}

		if (spring.getX() * scaling_factor > horizontal / 2 - 50)
		{
			scaling_factor = (horizontal / 2 - 50) / spring.getX();
		}

		if (spring.getX() > 0)
		{
			spring_rect.setPosition(horizontal / 2, vertical / 2 - 60);
			spring_rect.setSize(sf::Vector2f(scaling_factor * spring.getX(), 120));
		}
		else
		{
			spring_rect.setPosition(horizontal / 2 + scaling_factor * spring.getX(), vertical / 2 - 60);
			spring_rect.setSize(sf::Vector2f(abs(scaling_factor * spring.getX()), 120));
		}
		spring_rect.setTexture(&spring_texture);
		params.setString("Time: " + std::to_string(current_time) + " Position: " + std::to_string(spring.getX()) + " Velocity: " + std::to_string(spring.getV()) + " Acceleration: " + std::to_string(spring.getA()));

		window.draw(heading);
		window.draw(spring_rect);
		window.draw(params);

		window.display();

		machine_time = machine_time + (1 / float(fps));
	}
}

int main()
{
	getDesktopResolution(horizontal, vertical);

	float temp;
	std::cout << "---> Spring Motion <---";

	std::cout << "\n\nDo you want to use (1) Preset conditions or (2) Your own condition?: ";
	std::cin >> temp;

	if (temp == 1)
	{
		std::cout << "\nCondition 1: Damping, high frequency";
		std::cout << "\nCondition 2: No Damping, low frequency";
		std::cout << "\nYour Choice: ";
		std::cin >> temp;

		if (temp == 1)
		{
			spring.setX(50);
			spring.setV(0);
			spring_mass = 1;
			spring_constant = 40;
			damping_constant = 0.3;
			prec = 0.01;
			fps = 30;
		}
		else
		{
			spring.setX(50);
			spring.setV(0);
			spring_mass = 4;
			spring_constant = 1;
			damping_constant = 0;
			prec = 0.01;
			fps = 30;
		}
	}

	else
	{
		std::cout << "\n\nEnter initial position (with sign): ";
		std::cin >> temp;
		spring.setX(temp);

		std::cout << "Enter initial velocity (with sign): ";
		std::cin >> temp;
		spring.setV(temp);

		std::cout << "\nEnter mass of spring: ";
		std::cin >> spring_mass;

		std::cout << "Enter spring constant: ";
		std::cin >> spring_constant;

		std::cout << "Enter damping constant of medium: ";
		std::cin >> damping_constant;

		std::cout << "\nEnter precision required (recommended 0.01): ";
		std::cin >> prec;

		std::cout << "Enter framerate limit (recommended 30): ";
		std::cin >> fps;
	}

	spring_constant = -spring_constant / spring_mass;
	damping_constant = -damping_constant / spring_mass;
	current_time = 0;
	machine_time = 0;

	simulationLoop();
}

void getDesktopResolution(int& horizontal, int& vertical)
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void delay(float n_seconds)
{
	int milli = 1000 * n_seconds;

	clock_t start = clock();

	while (clock() < start + milli)
		;
}
