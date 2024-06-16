import os
import subprocess
import pytest
import filecmp
import json

# Global variables for easy configuration
BINARY_DIR = "./"              # Change this to the directory path of your binary
OUT_PATH = os.path.join(BINARY_DIR, "out.dat")
BINARY_NAME = "your_binary"    # Change this to the name of your binary
BINARY_FULL = os.path.join(BINARY_DIR, BINARY_NAME)
TEST_FILE_PATH = "test_files"  # Directory where the test files are located

@pytest.fixture(autouse=True)
def cleanup():
    yield
    if os.path.exists(OUT_PATH):
        os.remove(OUT_PATH)

@pytest.mark.parametrize("test_file", [f for f in os.listdir(TEST_FILE_PATH) if f.endswith(".dat")])
def test_serialization(test_file):
    # Construct full paths to files
    test_file_path = os.path.join(TEST_FILE_PATH, test_file)
    json_file_path = os.path.join(TEST_FILE_PATH, f"{os.path.splitext(test_file)[0]}.json")

    # Run the binary with the test file as the argument
    result = subprocess.run([BINARY_FULL, test_file_path], capture_output=True, text=True)

    # Check the stdout output
    assert result.returncode == 0, f"Error running {BINARY_NAME} with {test_file}"

    # Load expected output from JSON
    with open(json_file_path, 'r') as json_file:
        expected_data = json.load(json_file)

    # Parse stdout into a dictionary-like structure
    parsed_output = parse_output(result.stdout.strip())
    converted_output = {key: int(value) if value.isdigit() else value for key, value in parsed_output.items()}


    # Compare parsed output with the expected data
    assert converted_output == expected_data, f"Output mismatch for {test_file}"

    # Compare the out.dat file with the original file
    assert os.path.exists(OUT_PATH), "out.dat file was not created"
    assert filecmp.cmp(OUT_PATH, test_file_path), f"Serialized file mismatch for {test_file}"

def parse_output(output_str):
    lines = output_str.splitlines()
    data = {}

    for line in lines:
        key_value = line.split(": ", 1)
        if len(key_value) == 2:
            key, value = key_value
            data[key.strip()] = value.strip()

    return data
