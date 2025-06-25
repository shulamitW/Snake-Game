#include "SlimeEntity.h"
#include <filesystem>
using namespace cv;
using namespace std;
namespace fs = std::filesystem;

EntityPtr createSlime(std::string const& animationFolder)
{
	fs::path root = animationFolder;
	auto SlimeFolder = root / "D:\C++\Mario Game\Day1\Animations\SlimeOrange";

	auto MySlime = CreateSlimeEnemy(animationFolder);
	EntityPtr slime(new Entity(MySlime));
	return slime;
}
EntityStatePtr CreateSlimeEnemy(std::string const& animationFolder)
{
	AnimationPtr animation(new Animation(animationFolder));
	bool isCyclic = true;

	IGraphicsComponentPtr graphicsPtr(
		new SingleAnimationGraphics(animation, isCyclic));

	IPhysicsComponentPtr physicsPtr = make_shared<FixedWidgetPhysics>();

	return make_shared<EntityState>(graphicsPtr, physicsPtr);
}