﻿// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/framework/task_scheduler.hpp>




BEGIN_NAMESPACE(FE::framework)

void game_thread::__main(game_thread* const this_p)
{
	while (this_p->m_is_interrupted == false)
	{
	}
}

void game_thread::run()
{
	this->m_thread = std::thread(__main, this);
}

void game_thread::shutdown()
{
	this->m_thread.join();
}

END_NAMESPACE