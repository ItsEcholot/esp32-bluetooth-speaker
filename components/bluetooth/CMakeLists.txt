set(srcs "controller/bt.c")
idf_component_register(SRCS "bluetooth_avrcp.c" "bluetooth_controller.c" "bluetooth_bluedroid.c" "bluetooth_gap.c" "bluetooth_a2dp.c" "bluetooth_avrcp.c"
                       INCLUDE_DIRS "."
                       REQUIRES bt bluetooth_service)