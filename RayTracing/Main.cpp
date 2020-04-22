#include <iostream>
#include <memory>
#include "Scene.h"
#include "Timer.h"

int main()
{
	int nx = 400;
	int ny = 200;
	int ns = 500;

	std::cout << "処理開始" << std::endl;
	Timer time;
	time.Start();
	std::unique_ptr<Scene> scene = std::make_unique<Scene>(nx, ny, ns);
	(*scene).Render();
	std::cout << "処理終了：" << time.GetTime() << "秒" << std::endl;

	return 0;
}
