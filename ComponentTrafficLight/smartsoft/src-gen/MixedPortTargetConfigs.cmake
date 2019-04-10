# target configurations for ComponentTrafficLightROSExtension
IF(EXISTS ${ROS_DIR})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${ROS_LIBS})
ENDIF(EXISTS ${ROS_DIR})

# target configurations for PlainOpcUaComponentTrafficLightExtension
IF(open62541_FOUND)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} open62541)
TARGET_COMPILE_DEFINITIONS(${PROJECT_NAME} PUBLIC HAS_OPCUA)
ENDIF(open62541_FOUND)

