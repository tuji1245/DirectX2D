#pragma once
#include <memory>
#include "safe_release.h"

namespace Engine2D
{
	template <class T>
	class Singleton
	{
	protected:
		Singleton() {};
		virtual ~Singleton() {};
		template<class... Types>
		void Init(Types... values) {};
		virtual void Uninit() {};

	public:
		inline static std::weak_ptr<T> GetInstance()
		{
			return instance;
		}
		template<typename... Types>
		static void CreateInstance(Types... values)
		{
			DestoryInstance();
			instance.reset(new T);
			instance->Init(values...);
		}
		static void DestoryInstance()
		{
			safe_release(instance);
		}

	private:
		inline static std::shared_ptr<T> instance;
	};
}