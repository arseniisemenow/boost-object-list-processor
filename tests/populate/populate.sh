
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "Human_1", "x": 100, "y": 50, "type": "Human", "metadata": {"Age": 32}}' \
http://localhost:8080/v1/object
echo
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "Human_2", "x": 50, "y": 150, "type": "Human", "metadata": {"Age": 54}}' \
http://localhost:8080/v1/object
echo
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "Human_3", "x": 150, "y": 150, "type": "Human", "metadata": {"Age": 28}}' \
http://localhost:8080/v1/object
echo
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "Tree_1", "x": 250, "y": 150, "type": "Tree", "metadata": {"Age": 28, "Height": 6}}' \
http://localhost:8080/v1/object
echo
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "Tree_2", "x": 250, "y": 350, "type": "Tree", "metadata": {"Age": 15, "Height": 4}}' \
http://localhost:8080/v1/object
echo
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "Bush", "x": 450, "y": 350, "type": "Bush", "metadata": {"Age": 2, "Radius": 2}}' \
http://localhost:8080/v1/object
echo
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "Bush", "x": 450, "y": 550, "type": "Bush", "metadata": {"Age": 2.2, "Radius": 2.5}}' \
http://localhost:8080/v1/object
echo
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "Bush", "x": 450, "y": 650, "type": "Bush", "metadata": {"Age": 4.2, "Radius": 3.5}}' \
http://localhost:8080/v1/object
echo
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "Building_1", "x": 4500, "y": 6500, "type": "Building", "metadata": {"Width": 15, "Length": 10, "Depth": 20}}' \
http://localhost:8080/v1/object
echo
curl -X POST -H "Content-Type: application/json" \
-d '{"name": "Building_2", "x": 14500, "y": 16500, "type": "Building", "metadata": {"Width": 150, "Length": 40, "Depth": 40}}' \
http://localhost:8080/v1/object
echo

# Retrieve all objects
#curl -H "Content-Type: application/json" "http://localhost:8080/v1/object?NON_EXIST_PARAM=AMONGUS"
#curl -H "Content-Type: application/json" "http://localhost:8080/v1/object?group_by=NON_EXIST_VALUE"
#curl -H "Content-Type: application/json" "http://localhost:8080/v1/object?group_by=name"
#curl -H "Content-Type: application/json" "http://localhost:8080/v1/object?group_by=type&min_count=1"
#curl -H "Content-Type: application/json" "http://localhost:8080/v1/object?group_by=time"
#curl -H "Content-Type: application/json" "http://localhost:8080/v1/object?group_by=distance"
