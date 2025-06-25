#include "Animation.h"
#include <opencv2/opencv.hpp>


cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
cv::Mat canvas = background.clone();
cv::Point walkRight(cv::Point topLeft)
{
	topLeft.x += 10;
	return topLeft;
}
void idle(cv::Point topLeft)
{
	Animation animation(R"(../Animations/Hero/idle)");
	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
	int key = cv::waitKey(100);
	while (key != 'a')
	{
		for (int i = 0; i < animation.numFrames(); i++)
		{
			Frame const& frame = animation.getFrame(i);
			cv::Mat canvas = background.clone();
			cv::Point topLeft(canvas.size().width / 2, canvas.size().height * 4.4 / 6);
			drawFrame(frame, canvas, topLeft);
			cv::imshow("test", canvas);
			key = cv::waitKey(100);
		}
	}
}
void duck(cv::Point topLeft)
{
	Animation animation(R"(../Animations/Hero/duckDown)");
	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
	int key = cv::waitKey(100);

	for (int i = 0; i < animation.numFrames(); i++)
	{
		Frame const& frame = animation.getFrame(i);
		cv::Mat canvas = background.clone();

		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		key = cv::waitKey(100);

	}

	while (key != 'w')
	{
		Animation animation(R"(../Animations/Hero/duckStay)");
		Frame const& frame = animation.getFrame(0);
		cv::Mat canvas = background.clone();
	   // cv::Point topLeft(X, canvas.size().height * 4.4 / 6);
		//topLeft = walkRight(topLeft);
		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		key = cv::waitKey(100);
	}
	Animation animation_stand(R"(../Animations/Hero/standAfterDuck)");
	for (int i = 0; i < animation_stand.numFrames(); i++)
	{
		Frame const& frame = animation_stand.getFrame(i);
		cv::Mat canvas = background.clone();
		//cv::Point topLeft(X, canvas.size().height * 4.4 / 6);
		// = walkRight(topLeft);
		drawFrame(frame, canvas, topLeft);
		cv::imshow("test", canvas);
		key = cv::waitKey(100);
	}

}

cv::Point Right(cv::Point topLeft)
{
	Animation animation(R"(../Animations/Hero/runRight)");
	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
	int key = cv::waitKey(100);
	cv::Mat canvas = background.clone();
	int X = canvas.size().width/2;
	while (key != 'a'&& key != 's'&& key != 'w')
	{
		if (topLeft.x >= canvas.size().width - 100)
		{
			topLeft.x = 0;
		}
		for (int i = 0; i < animation.numFrames(); i++)
		{
			
			Frame const& frame = animation.getFrame(i);
			topLeft.x += + 10;
			cv::Mat canvas = background.clone();
			//cv::Point topLeft(topLeft.x, canvas.size().height * 4.4 / 6);
			drawFrame(frame, canvas, topLeft);
			cv::imshow("test", canvas);
			key = cv::waitKey(100);
		}
	}
	return  topLeft;
}
cv::Point jumpRight(cv::Point topLeft)
{
	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
	Animation animation(R"(../Animations/Hero/jump)");
	int key = cv::waitKey(100);
	cv::Mat canvas = background.clone();
	for (int i = 0; i < animation.numFrames()/2; i++)
	{
		Frame const& frame = animation.getFrame(i);
		cv::Mat canvas = background.clone();
		if (topLeft.x >= background.size().width)
		{
			topLeft.x = 0;
		}
		cv::imshow("test", canvas);
		topLeft.x += 10;
		topLeft.y +=10;
		key = cv::waitKey(100);
		//cv::Point topLeft(topLeft.x, topLeft.y);
		//topLeft = walkRight(topLeft);
		drawFrame(frame, canvas, topLeft);
		
		
	}
	for (int i = animation.numFrames() / 2; i < animation.numFrames() ; i++)
	{
		Frame const& frame = animation.getFrame(i);
		cv::Mat canvas = background.clone();
		topLeft.x+=10;
		topLeft.y -= 10;
		cv::imshow("test", canvas);
		topLeft = walkRight(topLeft);
		drawFrame(frame, canvas, topLeft);
		key = cv::waitKey(100);
	}
	//idle(topLeft);
	return topLeft;
}

int main1()
{
	cv::Point topLeft;
	cv::Mat background = cv::imread(R"(../Animations/background.png)", cv::IMREAD_UNCHANGED);
	int key = cv::waitKey(100);
	bool isToExit = false;
	Animation animation(R"(../Animations/Hero/runRight)");
	while (false == isToExit)
	{
		for (int i = 0; i < animation.numFrames(); i++)
		{
			Frame const& frame = animation.getFrame(i);
			cv::Mat canvas = background.clone();
			cv::Point topLeft(canvas.size().width / 2, canvas.size().height * 4.4 / 6);
			topLeft = walkRight(topLeft);
			drawFrame(frame, canvas, topLeft);
			cv::imshow("test", canvas);
			int key = cv::waitKey(100);
			if (key == 27)
			{
				isToExit = true;
			}
			//idle();
			if (key == 's')
				duck(topLeft);
			if (key == 'w')
				topLeft =jumpRight(topLeft);
			if (key == 'a')
				idle( topLeft);
			if (key == 'd')
				topLeft=Right(topLeft);
		}
	}
	return 0;
}
// 1.
// draws an animation of our hero that ducks in place, and stays down till you 
// press the 'w' key. (if (key == 'w'))

// 2.
// draws an animation of our hero that walks to the right, and ACTUALLLY MOVES RIGHT
// with a constant speed, of (1/10)*(image width) per 100 milliseconds (=0.1 second).


// 3.
// draw our hero jumps up and right, and stays standing after jump finishes.


// 4.
// write a main() that:
// when user presses 'd' - hero walks right
// when user presses 's' - hero ducks
// when user presses 'w' - hero jumps
// when user presses 'a' - hero stops (if it was walking right before)

// 5.
// in walkRight - when hero reaches the canvas boundery - don't let it go outside of image.
// force the hero x coordinate to be such that we'll see her.
// hint: you can get hero image cv::Mat with frame.image

// 6.
// do the same with jumpRight