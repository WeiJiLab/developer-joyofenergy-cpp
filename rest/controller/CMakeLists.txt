add_library(controller INTERFACE)
target_link_libraries(controller INTERFACE Boost::headers nlohmann_json::nlohmann_json service)
