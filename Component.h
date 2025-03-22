#pragma once
#include <memory>

class Component
{
public:
	virtual void Update() {};
	virtual bool IsRenderable() { return false; };
	virtual void Render(unsigned int transformMatrixId) = 0;
};

template<typename T, typename...Args>
std::shared_ptr<T> CreateObject(Args&&... args)
{
	return std::make_shared<T>(std::forward<Args>(args)...);
}