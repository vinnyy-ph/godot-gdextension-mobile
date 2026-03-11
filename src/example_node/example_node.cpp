#include "example_node.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

namespace godot {

void ExampleNode::_process(double delta) {
    time_passed += delta;
    // Uncomment to see output in the Godot console:
    // UtilityFunctions::print("Time: ", time_passed);
}

void ExampleNode::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_time_passed"), &ExampleNode::get_time_passed);
}

} // namespace godot
