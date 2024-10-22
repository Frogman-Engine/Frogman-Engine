// Copyright © from 2023 to current, UNKNOWN STRYKER. All Rights Reserved.
#include <FE/prerequisites.h>
#include <FE/framework/reflection/property.hpp>




BEGIN_NAMESPACE(FE::framework::reflection)

typename property::property_meta_data_map_type::mapped_type::allocator_type::pool_type property::s_node_pool;
typename property::property_meta_data_map_type*		property::s_property_map = nullptr;
typename property::class_layer_stack				property::s_class_layer;

typename property::lock_type                    property::s_lock;
typename property::file_handler                 property::s_fstream; 
typename property::input_buffer_type            property::s_input_buffer;
typename property::input_buffer_iterator_type   property::s_position;

END_NAMESPACE