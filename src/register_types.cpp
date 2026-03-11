#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

// ── Include your custom node headers here ────────────────────
// Example: #include "example_node/example_node.h"

using namespace godot;

void initialize_mobile_ext_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    // ── Register custom classes here ──────────────────────────
    // Example: ClassDB::register_class<ExampleNode>();
}

void uninitialize_mobile_ext_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
        return;
    }
    // Cleanup (usually not needed for simple extensions)
}

/// GDExtension entry point — Godot calls this automatically.
extern "C" {
GDEXTENSION_INIT_FUNC GDExtensionBool GDE_EXPORT
mobile_ext_library_init(
    GDExtensionInterfaceGetProcAddress p_get_proc_address,
    const GDExtensionClassLibraryPtr p_library,
    GDExtensionInitialization *r_initialization
) {
    godot::GDExtensionBinding::InitObject init_obj(
        p_get_proc_address, p_library, r_initialization
    );

    init_obj.register_initializer(initialize_mobile_ext_module);
    init_obj.register_terminator(uninitialize_mobile_ext_module);
    init_obj.set_minimum_library_initialization_level(
        MODULE_INITIALIZATION_LEVEL_SCENE
    );

    return init_obj.init();
}
}
