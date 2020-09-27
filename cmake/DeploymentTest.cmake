function(add_deploy_target ARG1)
	include(${PROJECT_SOURCE_DIR}/cmake/DeployDeviceIP.cmake)
	get_target_property(cDIR ${ARG1} BINARY_DIR)
	get_target_property(cNAME ${ARG1} NAME)
	add_custom_target(deploy_${cNAME}
		WORKING_DIRECTORY ${cDIR}
		COMMAND sshpass -p ${DEVICE_SSH_PASSWORD} scp "${cNAME}" "root@${DEVICE_IP}:~/deploy"
		&& sshpass -p ${DEVICE_SSH_PASSWORD} ssh "root@${DEVICE_IP}" "/root/deploy/${cNAME}"
	)
	add_dependencies(deploy_${cNAME} ${ARG1})
endfunction()
