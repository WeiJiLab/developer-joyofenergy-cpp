add_library(controller INTERFACE)

target_link_libraries(controller INTERFACE
    Boost::beast
    Boost::asio
    Boost::system
    nlohmann_json::nlohmann_json
    service
)
