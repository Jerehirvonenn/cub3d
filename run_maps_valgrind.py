import os
import subprocess

# Paths
cub3d_path = "./parsing/cub3d"  # Path to your cub3d executable
maps_dir = "./maps"     # Path to your maps directory

# Check if cub3d executable exists
if not os.path.isfile(cub3d_path):
    print(f"Error: {cub3d_path} not found. Ensure the executable exists.")
    exit(1)

# Check if maps directory exists
if not os.path.isdir(maps_dir):
    print(f"Error: {maps_dir} directory not found.")
    exit(1)

# Iterate over all files in the maps directory
for map_file in os.listdir(maps_dir):
    map_path = os.path.join(maps_dir, map_file)
    # Check if it's a file (not a directory)
    if os.path.isfile(map_path):
        print(f"Running: valgrind {cub3d_path} {map_path}")
        try:
            # Run cub3d with Valgrind to check for memory leaks
            subprocess.run(
                ["valgrind", "--leak-check=full", "--show-leak-kinds=all", "--track-origins=yes", cub3d_path, map_path],
                check=True
            )
        except subprocess.CalledProcessError as e:
            print(f"Error: Program exited with code {e.returncode}")

