// Copyright �� from 2024 to present, UNKNOWN STRYKER. All Rights Reserved. 
#include <FE/framework/reflection/private/load_reflection_data.h> 
#include <FE/framework/reflection.hpp> 
#include <FE/framework/framework.hpp> 
#include <C:/Users/leeho/OneDrive/����/GitHub/Frogman-Engine/SDK/Tests/FE-HT-Test/HeaderWithoutCopyright.hpp>

void load_reflection_data()
{
    ::FE::framework::framework_base::get_framework().get_method_reflection().register_task< ::FE::c_style_task<void(void*), typename ::FE::function<void(void*)>::arguments_type> >("FHT Gen ::FrogmanEngine::Math::Vector3()", &::FE::framework::reflection::construct_object<::FrogmanEngine::Math::Vector3>); 
    ::FE::framework::framework_base::get_framework().get_method_reflection().register_task< ::FE::c_style_task<void(void*), typename ::FE::function<void(void*)>::arguments_type> >("FHT Gen ::FrogmanEngine::Rendering::Renderer()", &::FE::framework::reflection::construct_object<::FrogmanEngine::Rendering::Renderer>); 
    ::FE::framework::framework_base::get_framework().get_method_reflection().register_task< ::FE::c_style_task<void(void*), typename ::FE::function<void(void*)>::arguments_type> >("FHT Gen ::FrogmanEngine::Utility::Timer()", &::FE::framework::reflection::construct_object<::FrogmanEngine::Utility::Timer>); 
}
