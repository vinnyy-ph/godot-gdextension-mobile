#ifndef REGISTER_TYPES_H
#define REGISTER_TYPES_H

#include <godot_cpp/core/class_db.hpp>

using namespace godot;

/// Called by Godot when the extension is loaded.
/// Register all your custom GDExtension classes here.
void initialize_mobile_ext_module(ModuleInitializationLevel p_level);

/// Called by Godot when the extension is unloaded.
void uninitialize_mobile_ext_module(ModuleInitializationLevel p_level);

#endif // REGISTER_TYPES_H
