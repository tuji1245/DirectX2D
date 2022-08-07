#pragma once
#include "pch.h"
#include <memory>
template<typename T>
void safe_release(std::shared_ptr<T>& pointer)
{
	if (std::shared_ptr<T> p = pointer)
		p.reset();
}