import subprocess
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import threading
import queue
import sys
import re

def run_program(command, output_queue):
    """Runs the given command and puts stdout lines into the queue."""
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True, bufsize=1)
    
    for line in process.stdout:
        output_queue.put(line.strip())
    
    process.stdout.close()
    process.wait()

def update_plot(frame, data_dict, output_queue, lines):
    """Fetches new data from the queue and updates the plot."""
    while not output_queue.empty():
        try:
            line = str(output_queue.get_nowait()).strip()
            if len(line) > 0: print(line) # update the stdout
            if line[:2] == "* " and line[-2:] == " *":
                line = line[2:-2]
                spl = line.split(":")
                key, value = spl[0].strip(), spl[1].strip()

                value = float(value)
                if key not in data_dict:
                    data_dict[key] = []
                data_dict[key].append(value)
                if len(data_dict[key]) > 200:  # Keep only the last 200 points
                    data_dict[key].pop(0)
        except Exception:
            pass  # Ignore invalid data
    
    ax.clear()
    for key, values in data_dict.items():
        ax.plot(range(len(values)), values, label=key)
    ax.legend()
    ax.relim()
    ax.autoscale_view()

    return lines

# Command to run the external program (modify as needed)
command = ["pros", "mut"]  # Example: Running another Python script

# Create a queue to store output
output_queue = queue.Queue()

# Start the external program in a separate thread
thread = threading.Thread(target=run_program, args=(command, output_queue), daemon=True)
thread.start()

# Set up the plot
fig, ax = plt.subplots()
data_dict = {}
ax.set_title("Real-time Output Plot")
ax.set_xlabel("Time Step")
ax.set_ylabel("Output Value")

# Start the animation
ani = animation.FuncAnimation(fig, update_plot, fargs=(data_dict, output_queue, []), interval=100)
plt.show()
