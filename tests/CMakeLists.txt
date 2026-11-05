set(KVSS_TEST_SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/nvs_test.c
        ${CMAKE_CURRENT_SOURCE_DIR}/flash_sim.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nvs/nvs.c
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/kvss/kvss_crc.c)

set(KVSS_TEST_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/kvss
        ${CMAKE_CURRENT_SOURCE_DIR}/../src/nvs)

function(kvss_add_nvs_test name)
    add_executable(${name} ${KVSS_TEST_SOURCES})
    target_include_directories(${name} PRIVATE ${KVSS_TEST_INCLUDES})
    target_compile_definitions(${name} PRIVATE
            CONFIG_ZTEST=1
            CONFIG_TEST_NVS_SIMULATOR=1
            CONFIG_NVS_INIT_BAD_MEMORY_REGION=1
            KVSS_PORT_LOG_IMPL=1
            ${ARGN})
    target_compile_options(${name} PRIVATE
            -Wall -Wextra
            -include ${CMAKE_CURRENT_SOURCE_DIR}/silent_log.h)
    add_test(NAME ${name} COMMAND ${name})
endfunction()

kvss_add_nvs_test(nvs_test)
kvss_add_nvs_test(nvs_test_cache
        CONFIG_NVS_LOOKUP_CACHE=1
        CONFIG_NVS_LOOKUP_CACHE_SIZE=64)
kvss_add_nvs_test(nvs_test_crc
        CONFIG_NVS_DATA_CRC=1)
kvss_add_nvs_test(nvs_test_crc_cache
        CONFIG_NVS_DATA_CRC=1
        CONFIG_NVS_LOOKUP_CACHE=1
        CONFIG_NVS_LOOKUP_CACHE_SIZE=64)

# Flash parameter variants, matching Zephyr's tests.yaml configurations.
add_test(NAME nvs_test_erase_0x00 COMMAND nvs_test --erase-value 0)
add_test(NAME nvs_test_no_explicit_erase COMMAND nvs_test --no-erase)
add_test(NAME nvs_test_64kb_sector COMMAND nvs_test --sector-size 65536)
add_test(NAME nvs_test_gc_pack COMMAND nvs_test --write-block-size 4)
add_test(NAME nvs_test_crc_0x00 COMMAND nvs_test_crc --erase-value 0)
