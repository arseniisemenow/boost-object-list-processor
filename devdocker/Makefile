IMAGE_NAME := devimage
CONTAINER_NAME := devcontainer

setup:
	docker compose up -d

remove_keys_hostname:
	ssh-keygen -R '[localhost]:2222'