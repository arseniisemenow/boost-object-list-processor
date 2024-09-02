#!/bin/bash

# Function to generate random coordinates between -5000 and 5000
generate_random_coords() {
    echo $(( ( $(od -An -N2 -i /dev/urandom | tr -d ' ') % 10001 ) - 5000 ))
}

# Tools
curl -X POST -H "Content-Type: application/json" \
-d "{\"name\": \"Spoon\", \"x\": $(generate_random_coords), \"y\": $(generate_random_coords), \"type\": \"Tool\", \"metadata\": {\"material\": \"stainless steel\"}}" \
http://localhost:8080/v1/object -v

echo
curl -X POST -H "Content-Type: application/json" \
-d "{\"name\": \"Fork\", \"x\": $(generate_random_coords), \"y\": $(generate_random_coords), \"type\": \"Tool\", \"metadata\": {\"material\": \"stainless steel\"}}" \
http://localhost:8080/v1/object -v

echo
# Furniture
curl -X POST -H "Content-Type: application/json" \
-d "{\"name\": \"Stool\", \"x\": $(generate_random_coords), \"y\": $(generate_random_coords), \"type\": \"Furniture\", \"metadata\": {\"material\": \"plastic\", \"height_cm\": 45}}" \
http://localhost:8080/v1/object -v

echo
curl -X POST -H "Content-Type: application/json" \
-d "{\"name\": \"Cabinet\", \"x\": $(generate_random_coords), \"y\": $(generate_random_coords), \"type\": \"Furniture\", \"metadata\": {\"material\": \"wood\", \"shelves\": 3}}" \
http://localhost:8080/v1/object -v

echo
# Dishes
curl -X POST -H "Content-Type: application/json" \
-d "{\"name\": \"Cup\", \"x\": $(generate_random_coords), \"y\": $(generate_random_coords), \"type\": \"Dish\", \"metadata\": {\"material\": \"ceramic\", \"volume_ml\": 250}}" \
http://localhost:8080/v1/object -v

echo
curl -X POST -H "Content-Type: application/json" \
-d "{\"name\": \"Bowl\", \"x\": $(generate_random_coords), \"y\": $(generate_random_coords), \"type\": \"Dish\", \"metadata\": {\"material\": \"glass\", \"diameter_cm\": 20}}" \
http://localhost:8080/v1/object -v

echo
# Meals
curl -X POST -H "Content-Type: application/json" \
-d "{\"name\": \"Salad with Cottage Cheese\", \"x\": $(generate_random_coords), \"y\": $(generate_random_coords), \"type\": \"Meal\", \"metadata\": {\"ingredients\": \"lettuce, tomato, cucumber, cottage cheese\", \"calories_kcal\": 150}}" \
http://localhost:8080/v1/object -v

echo
curl -X POST -H "Content-Type: application/json" \
-d "{\"name\": \"Grilled Cheese Sandwich\", \"x\": $(generate_random_coords), \"y\": $(generate_random_coords), \"type\": \"Meal\", \"metadata\": {\"ingredients\": \"bread, cheese, butter\", \"calories_kcal\": 300}}" \
http://localhost:8080/v1/object -v

echo
# Products
curl -X POST -H "Content-Type: application/json" \
-d "{\"name\": \"Eggs\", \"x\": $(generate_random_coords), \"y\": $(generate_random_coords), \"type\": \"Product\", \"metadata\": {\"category\": \"Dairy\", \"count\": 12}}" \
http://localhost:8080/v1/object -v

echo
curl -X POST -H "Content-Type: application/json" \
-d "{\"name\": \"Milk\", \"x\": $(generate_random_coords), \"y\": $(generate_random_coords), \"type\": \"Product\", \"metadata\": {\"category\": \"Dairy\", \"volume_liters\": 1}}" \
http://localhost:8080/v1/object -v

echo
# Recipes
curl -X POST -H "Content-Type: application/json" \
-d "{\"name\": \"Pancake Recipe\", \"x\": $(generate_random_coords), \"y\": $(generate_random_coords), \"type\": \"Recipe\", \"metadata\": {\"ingredients\": \"flour, milk, eggs, sugar\", \"servings\": 4}}" \
http://localhost:8080/v1/object -v

echo
curl -X POST -H "Content-Type: application/json" \
-d "{\"name\": \"Omelette Recipe\", \"x\": $(generate_random_coords), \"y\": $(generate_random_coords), \"type\": \"Recipe\", \"metadata\": {\"ingredients\": \"eggs, cheese, ham\", \"servings\": 2}}" \
http://localhost:8080/v1/object -v

echo
# Retrieve all objects
curl -H "Content-Type: application/json" \
http://localhost:8080/v1/object -v
