import serial
import requests

# Your ThingSpeak API key
api_key = "Your API Key"


def readserial(comport, baudrate):

    ser = serial.Serial(comport, baudrate, timeout=0.1)         # 1/timeout is the frequency at which the port is read

    while True:
        data = ser.readline().decode().strip()
        if data:
            print(data)
            pushData(data)

def pushData(data):
    # Split the data string into key-value pairs
    data_pairs = data.split(',')

    # Initialize a dictionary to store the values
    data_dict = {}

    # Iterate over each key-value pair and populate the dictionary
    for pair in data_pairs:
        key, value = pair.split(':')
        data_dict[key.strip('*')] = value

    # Extract values for each field
    humidity = data_dict["Humidity"]
    temp_c = data_dict["C"]
    temp_f = data_dict["F"]
    heat_index = data_dict["HeatIndex"]

    # Construct the URL with extracted values
    url = f"https://api.thingspeak.com/update?api_key={api_key}&field1={humidity}&field2={temp_c}&field3={temp_f}&field4={heat_index}"

    # Send the request to ThingSpeak
    response = requests.get(url)

    # Check the response
    if response.status_code == 200:
        print("Data sent successfully!")
    else:
        print(f"Failed to send data. Status code: {response.status_code}")


if __name__ == '__main__':

    readserial('COM3', 9600)


