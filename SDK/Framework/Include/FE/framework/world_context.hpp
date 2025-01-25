﻿#ifndef _FE_FRAMEWORK_WORLD_CONTEXT_HPP_
#define _FE_FRAMEWORK_WORLD_CONTEXT_HPP_
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
#include <FE/framework/framework.hpp>
#include <FE/framework/reflection.hpp>
#include <FE/framework/super_base.hpp>




BEGIN_NAMESPACE(FE::framework)


class world_context : public super_base
{
	FE_CLASS_HAS_A_BASE(super_base);
	FE_CLASS(world_context);

public:
	world_context() noexcept;
	virtual ~world_context() noexcept;

protected:
	virtual void on_construction() override;
	virtual void on_destruction() override;
};

END_NAMESPACE
#endif