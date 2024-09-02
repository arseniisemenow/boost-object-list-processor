IMAGE_NAME := devimage
CONTAINER_NAME := devcontainer

docker_image:
	docker build -t ${IMAGE_NAME} .
docker_container:
	docker run -d -p 2222:22 --name ${CONTAINER_NAME} ${IMAGE_NAME}

docker_remove_container:
	-docker stop ${CONTAINER_NAME} && docker rm ${CONTAINER_NAME}

rebuild: docker_remove_container docker_image docker_container

remove_keys_hostname:
	ssh-keygen -R '[localhost]:2222'