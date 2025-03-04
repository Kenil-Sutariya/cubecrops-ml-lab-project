from flask import Flask, jsonify, request
import csv
import os
from datetime import datetime

app = Flask(__name__)

# Define the authorization token
AUTH_TOKEN = "**************"

# Ensure the CSV file exists and write the header if not present
csv_file = "/home/my_api/sensor_data.csv"
if not os.path.exists(csv_file):
    with open(csv_file, mode="w", newline="") as file:
        writer = csv.writer(file)
        writer.writerow(["timestamp", "height_1", "height_2", "temperature", "humidity"])  # Header row

@app.route('/api/ping', methods=['GET'])
def ping():
    # Check for the Authorization header
    auth_header = request.headers.get("Authorization")
    if not auth_header or not auth_header.startswith("Bearer ") or auth_header.split(" ")[1] != AUTH_TOKEN:
        return jsonify({"error": "Unauthorized"}), 401

    # Retrieve query parameters
    height_1 = request.args.get('height_1')
    height_2 = request.args.get('height_2')
    temperature = request.args.get('temperature')
    humidity = request.args.get('humidity')

    # Check if all parameters are provided
    if not all([height_1, height_2, temperature, humidity]):
        return jsonify({"error": "Missing one or more sensor values"}), 400

    # Log the data to the terminal
    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    data = {"timestamp": timestamp, "height_1": height_1, "height_2": height_2, "temperature": temperature, "humidity": humidity}
    print(f"Received data: {data}")

    # Save the data to the CSV file
    with open(csv_file, mode="a", newline="") as file:
        writer = csv.writer(file)
        writer.writerow([timestamp, height_1, height_2, temperature, humidity])

    return jsonify({"status": "success", "received": data}), 200

if __name__ == '__main__':
    app.run(debug=True, host='0.0.0.0', port=6001)
