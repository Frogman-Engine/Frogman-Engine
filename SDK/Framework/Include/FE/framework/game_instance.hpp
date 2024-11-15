﻿#ifndef _FE_FRAMEWORK_GAME_INSTANCE_HPP_
#define _FE_FRAMEWORK_GAME_INSTANCE_HPP_
/*
Copyright © from 2022 to present, UNKNOWN STRYKER. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/
#include <FE/prerequisites.h>
#include <FE/framework/atom_base.hpp>
#include <FE/framework/game_thread.hpp>
#include <FE/framework/input_manager.hpp>




BEGIN_NAMESPACE(FE::framework)


class game_instance : public atom_base
{
	FE_CLASS(game_instance);
	FE_CLASS_HAS_A_BASE(atom_base);

	game_thread m_game_thread;

public:
	game_instance() noexcept;
	virtual ~game_instance() noexcept override;

protected:
	virtual void on_construction() override;
	virtual void on_destruction() override;

	virtual void tick(FE::float64 delta_second_p) override;

public:
	virtual void serialize() override;
	virtual void deserialize() override;
};

END_NAMESPACE
#endif