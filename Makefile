all: populate get_all_objects get_all_objects_group_by_distance get_all_objects_group_by_name get_all_objects_group_by_time get_all_objects_group_by_type

1: get_all_objects
2: populate
3: delete_all_objects

populate:
	sh tests/populate/populate.sh
populate_python:
	python3 tests/populate/populate.py

get_all_objects:
	sh tests/get_all_objects/get_all_objects.sh
get_all_objects_group_by_distance:
	sh tests/get_all_objects/get_all_objects_group_by_distance.sh
get_all_objects_group_by_name:
	sh tests/get_all_objects/get_all_objects_group_by_name.sh
get_all_objects_group_by_time:
	sh tests/get_all_objects/get_all_objects_group_by_time.sh
get_all_objects_group_by_type:
	sh tests/get_all_objects/get_all_objects_group_by_type.sh

delete_all_objects:
	sh tests/delete_all_objects/delete_all_objects.sh

install: run_server install_client
uninstall: uninstall_server uninstall_client

run_server:
	docker compose up -d

cli:
	./build-client/object-list-processor-client

install_client:
	mkdir -p build-client && cd build-client && cmake ..
	cd build-client && cmake --build . --target object-list-processor-client
install_server:
	mkdir -p build-server && cd build-server && cmake ..
	cd build-server && cmake --build . --target object-list-processor-server

uninstall_client:
	rm -rf build-client
uninstall_server:
	rm -rf build-server

# In case use face this error:
# failed to solve: ubuntu:20.04: error getting credentials - err:
# exec: "docker-credential-desktop": executable file not found in $PATH, out: ``
fix_docker:
	sed -ie 's/credsStore/credStore/g' ~/.docker/config.json