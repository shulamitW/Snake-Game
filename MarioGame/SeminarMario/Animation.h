#pragma once

#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>
//frame for each image
class Frame
{
public:
	cv::Mat image; // rgb
	cv::Mat mask; // alpha //שקיפות
public:
	Frame(std::string const& path); // טוען את התמונה
	bool isValid() const; // check if image is valid wasl loaded
};
//מצייר את התמונה על המסך שזה הסורס במקום לפי הנקודה שקיבל
void drawFrame(Frame const& src, cv::Mat & dst, cv::Point const& TL);


class Animation
{
private:
	std::vector<Frame> _frames;

public:
	//מקבל את התקייה ומאתחל את הווקטור של _frames 
	Animation(std::string const& folder);
	Frame const& getFrame(size_t idx);
	size_t numFrames() const;
};

typedef std::shared_ptr<Animation> AnimationPtr;