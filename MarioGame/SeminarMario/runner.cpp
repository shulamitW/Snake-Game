#include "Animation.h"
#include <opencv2/opencv.hpp>
#include "Timer.h"
#include "HeroEntity.h"

// @2: include the slime enemy:
#include "SlimeEntity.h"
// @2: no need to write cv:: every time, we can just use namespace:
using namespace cv;
// @2: NOTE! you should "use namespace" only in cpp file, NOT in H files! (because it "passes on" with the #include statement.)


// before you start: open SeminarMario project properties, go to 
// Debugging -> Environment
// set the following value:
// PATH=$(PATH);../OpenCV_451/bin
// hit Ctrl + F5 and see a walking lady. that's our hero!
// press Esc to exit.
// read carefully the comments below - it contains explanations and instructions.
// and do the exercises.

int main()
{

	Mat background = imread(R"(../Animations/background.png)", IMREAD_UNCHANGED);

	auto slimeState = CreateSlimeEnemy(R"(../Animations/SlimeOrange)");
	slimeState->reset(Point(background.size().width * 2 / 3, background.size().height * 4 / 5));
	
	//auto slimeEnemy = createSlime(R"(../Animations/SlimeOrange)");
	//slimeEnemy->reset(Point(background.size().width * 1 / 2, background.size().height * 3 / 5));

	EntityPtr hero = createHero(R"(../Animations/Hero)");
	hero->reset(Point(background.size().width /25, background.size().height * 2 / 3));
	

	EntityPtr slime(new Entity(slimeState));
	Timer timer(/*freq. ms=*/100);
	timer.Register(slime);
	timer.Register(hero);

	bool isToExit = false;
	while (false == isToExit)
	{
		Mat canvas = background.clone();

		timer.tick();
		//slimeEnemy->draw(canvas);
		slime->draw(canvas);
		hero->draw(canvas);
		
		imshow("test", canvas);
		imwrite("test.jpg", canvas);
	}

	return 0;
}

// 1.
// draws an animation of our hero that ducks in place, and stays down till you 
// press the 'w' key. (if (key == 'w'))
void duck();

// 2.
// draws an animation of our hero that walks to the right, and ACTUALLLY MOVES RIGHT
// with a constant speed, of (1/10)*(image width) per 100 milliseconds (=0.1 second).
void walkRight();

// 3.
// draw our hero jumps up and right, and stays standing after jump finishes.
void jumpRight();

// 4.
// write a main() that:
// when user presses 'd' - hero walks right
// when user presses 's' - hero ducks
// when user presses 'w' - hero jumps
// when user presses 'a' - hero stops (if it was walking right before)

// 5.
// in walkRight - when hero reaches the canvas boundery - don't let it go outside of image.
// force the hero x coordinate to be such that we'll see her.

// 6.
// do the same with jumpRight