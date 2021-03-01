import os
import sys
import csv
import math
import subprocess

program_path = "bin/file_processor"
number_of_executions = 5

def main():
    
    file_sizes = [30, 1000, 10000, 100000, 1000000, 10000000, 100000000]

    min_times = {}
    max_times = {}

    for file_size in file_sizes:
        best_times = {}
        test_file_name = f"{file_size}.input"
        test_file_path = os.path.join("testes", f"{test_file_name}")
        verification_file_path = os.path.join("testes", f"{file_size}.txt")
        verification_data = get_verification_data(verification_file_path)

        buffer_size_start = 2 if file_size < 100000000 else 1024

        available_block_sizes = [i for i in powers_of_two_generator(file_size)]
        available_buffer_sizes = [i for i in powers_of_two_generator(file_size, buffer_size_start)]

        available_combinations = [[i, j] for i in available_block_sizes
                                         for j in available_buffer_sizes]


        for index, combination in enumerate(available_combinations):
            print(f"Running combination {index + 1} of {len(available_combinations)} for file: {test_file_name}...")

            block_size = combination[0]
            buffer_size = combination[1]
            
            best_time = get_best_execution_time_data(block_size, buffer_size, test_file_path, verification_data)

            best_times[(block_size, buffer_size)] = best_time
        
        min_times[file_size] = find_min_time(best_times)
        max_times[file_size] = find_max_time(best_times)

        output_best_times(best_times, file_size)
    
    output_summary(file_sizes, min_times, max_times)


def run_program_params(program_path, *params):
    return subprocess.run([program_path, *params], stdout=subprocess.PIPE).stdout.decode()

def confirm_response(program_response, verification_data):
    response_lines = program_response.splitlines()

    for index, line in enumerate(verification_data.splitlines()):
        if line != response_lines[index]:
            return False
    
    return True

def get_verification_data(verification_file_path):
    with open(verification_file_path, "r") as f:
            f.readline() # First line is discarded
            verification_data = f.read()

    return verification_data

def get_time(program_response):
    time_line = program_response.splitlines()[-1]
    time_str = time_line.replace("Time: ", "").replace("s", "")

    return float(time_str)

def get_best_execution_time_data(block_size, buffer_size, test_file_path, verification_data):
    times = []

    for _ in range(number_of_executions):
        program_response = run_program_params(program_path, f"{block_size}", f"{buffer_size}", test_file_path)

        is_correct = confirm_response(program_response, verification_data)

        if not is_correct:
            report_error_and_exit(program_response, verification_data, block_size, buffer_size)
        
        time = get_time(program_response)
        times.append(time)
    
    return min(times)

def find_min_time(best_times):
    current_min_key = None
    current_min_time = math.inf

    for key, time in best_times.items():
        if time < current_min_time:
            current_min_key = key
            current_min_time = time
    
    (block_size, buffer_size) = current_min_key
    return [block_size, buffer_size, current_min_time]

def find_max_time(best_times):
    current_max_key = None
    current_max_time = -math.inf

    for key, time in best_times.items():
        if time > current_max_time:
            current_max_key = key
            current_max_time = time
    
    (block_size, buffer_size) = current_max_key
    return [block_size, buffer_size, current_max_time]

def powers_of_two_generator(upper_bound, start=2):
    i = start
    while i <= upper_bound:
        yield i
        i *= 2

def report_error_and_exit(program_response, verification_data, block_size, buffer_size):
    print(f"Verification failed for block size: {block_size} and buffer size: {buffer_size}")
    print("\nExpected:")
    print(verification_data)
    print("\nGot:")
    print(program_response)

    sys.exit(1)

def output_best_times(best_times, file_size):
    output_directory = "results"
    output_file = os.path.join(output_directory, f"times_{file_size}.csv")

    if not os.path.exists(output_directory):
        os.makedirs(output_directory)

    best_times_csv = best_times_to_csv_format(best_times)

    with open(output_file, "w") as f:
        writer = csv.writer(f, dialect='excel')
        writer.writerows(best_times_csv)

def output_summary(file_sizes, min_times, max_times):
    output_directory = "results"
    output_file = os.path.join(output_directory, "summary.csv")

    if not os.path.exists(output_directory):
        os.makedirs(output_directory)

    summary_csv = summary_to_csv_format(file_sizes, min_times, max_times)

    with open(output_file, "w") as f:
        writer = csv.writer(f, dialect='excel')
        writer.writerows(summary_csv)

def best_times_to_csv_format(best_times):
    rows = [["block size", "buffer size", "time"]]

    for (block_size, buffer_size), time in best_times.items():
        rows.append([block_size, buffer_size, time])

    return rows

def summary_to_csv_format(file_sizes, min_times, max_times):
    rows = [["file size", "min block size", "min buffer size", "min time", "max block size", "max buffer size", "max time"]]

    for file_size in file_sizes:
        min_time = min_times[file_size]
        max_time = max_times[file_size]

        rows.append([file_size, *min_time, *max_time])
    
    return rows

if __name__ == "__main__":
    main()