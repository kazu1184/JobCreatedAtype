#pragma once
//======================================================
// File Name	: GameContext.h
// Summary		: ゲームコンテキスト
// Date			: 2019/012/09
// Author		: Kazuaki Hashimoto
//======================================================

#include<memory>

template<typename Context>
class GameContext
{
	private:
		static Context* sContext;

	public:
		static void Register(const std::unique_ptr<Context>& context)
		{
			sContext = context.get();
		}

		static Context* Get()
		{
			return sContext;
		}
};

template<typename Context>
Context* GameContext<Context>::sContext = nullptr;

