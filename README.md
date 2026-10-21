# Pi System Monitor

A small real-time terminal dashboard for the Raspberry Pi, written in C++. It shows CPU usage, memory usage, and CPU temperature, refreshes every second, and logs every reading to a CSV file so you can look back at how the Pi behaved over time.

There are no monitoring libraries involved. Every number comes straight from the files the Linux kernel exposes under `/proc` and `/sys`.

```
===========================================
    Pi System Monitor
===========================================
  CPU     [###-----------------]    15.0%
  Memory  [##############------]    69.3%
  Temp    51.0 C
===========================================

Press 'q' to quit
```

## What it reads

| Metric      | Source                                    | How it's calculated |
|-------------|-------------------------------------------|---------------------|
| CPU usage   | `/proc/stat` (first `cpu` line)           | Compares busy time vs. idle time between two reads one second apart. A single read only gives totals since boot, so the delta is what turns it into "usage right now." |
| Memory      | `/proc/meminfo`                           | `MemTotal − MemAvailable`, converted from kB to GB. `MemAvailable` is used instead of `MemFree` because Linux uses spare RAM for cache, and `MemFree` would make the Pi look almost full. |
| Temperature | `/sys/class/thermal/thermal_zone0/temp`   | The kernel reports millidegrees Celsius, so the value is divided by 1000. |

## Requirements

- A Raspberry Pi (or any Linux machine; temperature needs a `thermal_zone0`)
- A C++17 compiler (`g++`)
- CMake 3.10+
- ncurses

On Raspberry Pi OS / Debian / Ubuntu:

```bash
sudo apt update
sudo apt install build-essential cmake libncurses-dev
```

## Build and run

```bash
git clone https://github.com/Minhbui100/SystemMonitor.git
cd SystemMonitor
mkdir -p build && cd build
cmake ..
make
./sysmonitor
```

Press **q** to quit. The terminal is restored to normal when the program exits.

## The CSV log

Every second, a row is appended to `Report.csv` in the folder you ran the program from. The header is written once, the first time the file is created, so running the monitor again keeps adding to the same log.

```
timestamp,cpu_pct,mem_used_gb,mem_total_gb,temp_c
2026-06-26T11:10:28,6.0,0.6,0.9,51.0
2026-06-26T11:10:29,3.0,0.6,0.9,51.0
2026-06-26T11:10:30,15.0,0.6,0.9,51.0
```

You can open it in Excel or load it with pandas to chart temperature against CPU load, which is handy for checking whether a case or heatsink is doing its job.

## How the code is organized

Each metric has its own collector class, and they all share one small interface:

```cpp
class Collector {
public:
    virtual void update() = 0;
    virtual ~Collector() = default;
};
```

`SystemMonitor` owns the collectors in a `std::vector<std::unique_ptr<Collector>>` and refreshes all of them with one loop. Adding a new metric, like disk usage or network throughput, means writing one new class and registering it in the constructor. The dashboard and logger don't need to change their update logic.

```
include/                 src/
├── Collector.h          ├── main.cpp             # ncurses dashboard + 1-second loop
├── CpuCollector.h       ├── CpuCollector.cpp     # /proc/stat
├── MemoryCollector.h    ├── MemoryCollector.cpp  # /proc/meminfo
├── TempCollector.h      ├── TempCollector.cpp    # /sys/class/thermal
├── SystemMonitor.h      ├── SystemMonitor.cpp    # owns and updates collectors
└── Logger.h             └── Logger.cpp           # appends rows to Report.csv
```
