import random
import requests
import json

def generate_random_coords():
    return round(random.uniform(-7000, 7000), 2)

def generate_metadata(item_type):
    if item_type == "Tree":
        return {"height": random.choice([5, 10, 15, 20, 25]), "age": random.randint(1, 100)}
    elif item_type == "Bush":
        return {"width": random.choice([2, 4, 6, 8]), "has_flowers": random.randint(1, 3)}
    elif item_type == "Doghouse":
        return {"size": random.choice(["small", "medium", "large"]), "is_insulated":  random.randint(0, 1)}
    elif item_type == "Swing":
        return {"material": random.choice(["wood", "metal"]), "capacity": random.randint(1, 3)}
    elif item_type == "Hammock":
        return {"facing_direction": random.choice(["north", "south", "east", "west"])}
    else:
        return {"description": "A garden element"}

garden_items = [
    "Tree", "Bush", "Doghouse", "Swing", "Hammock"
]

url = "http://localhost:8080/v1/object"
headers = {"Content-Type": "application/json"}

for i in range(1, 21):
    item_type = random.choice(garden_items)
    data = {
        "name": f"{item_type}_{i}",
        "x": generate_random_coords(),
        "y": generate_random_coords(),
        "type": f"{item_type}",
        "metadata": generate_metadata(item_type)
    }

    # Ensure the metadata is properly formatted as JSON
    try:
        # metadata_str = json.dumps(data["metadata"])
        # data["metadata"] = metadata_str

        response = requests.post(url, headers=headers, data=json.dumps(data))
        if response.status_code == 201:
            print(f"Added {item_type}_{i}: {response.status_code}, {response.json()}")
        else:
            print(f"Failed to add {item_type}_{i}: {response.status_code}, {response.json()}")
    except Exception as e:
        print(f"Error with {item_type}_{i}: {e}")


