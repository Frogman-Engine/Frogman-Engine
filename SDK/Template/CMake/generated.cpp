// Copyright �� from 2024 to present, UNKNOWN STRYKER. All Rights Reserved. 
#include <FE/framework/reflection/private/load_reflection_data.h> 
#include <FE/framework/reflection.hpp> 
#include <FE/framework/framework.hpp> 
#include <C:/Users/leeho/OneDrive/����/GitHub/Frogman-Engine/SDK/Tests/FE-HT-Test/HeaderWithoutCopyright.hpp>

void load_reflection_data()
{
    ::FE::framework::framework_base::get_engine().get_method_reflection().register_task< ::FE::c_style_task<void(void*), typename ::FE::function<void(void*)>::arguments_type> >("FHT Gen ::FrogmanEngineMathVector3()", &::FE::framework::reflection::construct_object<::FrogmanEngineMathVector3>); 
    ::FE::framework::framework_base::get_engine().get_method_reflection().register_task< ::FE::c_style_task<void(void*), typename ::FE::function<void(void*)>::arguments_type> >("FHT Gen ::FrogmanEngineRenderingRenderer()", &::FE::framework::reflection::construct_object<::FrogmanEngineRenderingRenderer>); 
    ::FE::framework::framework_base::get_engine().get_method_reflection().register_task< ::FE::c_style_task<void(void*), typename ::FE::function<void(void*)>::arguments_type> >("FHT Gen ::FrogmanEngineUtilityTimer()", &::FE::framework::reflection::construct_object<::FrogmanEngineUtilityTimer>); 
}
