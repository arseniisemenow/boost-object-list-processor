curl -X POST -H "Content-Type: application/json" \
-d '{"name": "Monitor", "x": 0.01, "y": 0.02, "type": "Tech device", "creation_time": 1.23}' \
http://localhost:8080/v1/object -v
echo
curl -H "Content-Type: application/json" \
http://localhost:8080/v1/object -v

#curl -X POST -H "Content-Type: application/json" -d '{"name": "John Doe", "age": 30}' http://localhost:6969/v1/person -v
