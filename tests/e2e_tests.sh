#!/bin/bash

# Function to generate random coordinates between -5000 and 5000
generate_random_coords() {
    echo $(( ( $(od -An -N2 -i /dev/urandom | tr -d ' ') % 10001 ) - 5000 ))
}

curl -X POST -H "Content-Type: application/json" \
-d '{"name": "AAMouse", "x": 125.23, "y": 0.20, "type": "Tech device", "metadata": {"speed": 100}}' \
http://localhost:8080/v1/object -v
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "AAMouse", "x": 125.23, "y": 0.20, "type": "Tech device", "metadata": {"speed": 150}}' \
http://localhost:8080/v1/object -v
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "BBMouse", "x": 125.23, "y": 0.20, "type": "Tech device", "metadata": {"speed": 200}}' \
http://localhost:8080/v1/object -v
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "ABMouse", "x": 125.23, "y": 0.20, "type": "Tech device", "metadata": {"speed": 300}}' \
http://localhost:8080/v1/object -v
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "BAMouse", "x": 125.23, "y": 0.20, "type": "Tech device", "metadata": {"speed": 400}}' \
http://localhost:8080/v1/object -v

## Retrieve all objects
#curl -H "Content-Type: application/json" \
#http://localhost:8080/v1/object -v
# Retrieve all objects
curl -H "Content-Type: application/json" "http://localhost:8080/v1/object?group_by=name"
curl -H "Content-Type: application/json" http://localhost:8080/v1/object? -v