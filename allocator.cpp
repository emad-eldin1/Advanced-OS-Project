#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Structure to represent a memory region (allocated or free)
struct MemoryRegion {
    int startAddress;
    int size;
    string processName; // Process name if allocated, empty if free

    MemoryRegion(int start, int s, string name = "") : startAddress(start), size(s), processName(name) {}
};

// Function to compare memory regions based on start address (for sorting)
bool compareRegions(const MemoryRegion& a, const MemoryRegion& b) {
    return a.startAddress < b.startAddress;
}

class MemoryAllocator {
public:
    MemoryAllocator(int totalSize) : totalMemorySize(totalSize) {
        memoryRegions.push_back(MemoryRegion(0, totalSize)); // Initially, the entire memory is free
    }

    void requestMemory(int size, string processName, char allocationStrategy) {
        int bestFitIndex = -1;
        int minDiff = totalMemorySize + 1;
        int firstFitIndex = -1;
        int worstFitIndex = -1;
        int maxFreeSize = -1;

        for (int i = 0; i < memoryRegions.size(); ++i) {
            if (memoryRegions[i].processName.empty() && memoryRegions[i].size >= size) {
                // First-fit
                if (firstFitIndex == -1) {
                    firstFitIndex = i;
                }

                // Best-fit
                int diff = memoryRegions[i].size - size;
                if (diff < minDiff) {
                    minDiff = diff;
                    bestFitIndex = i;
                }

                // Worst-fit
                if (memoryRegions[i].size > maxFreeSize) {
                    maxFreeSize = memoryRegions[i].size;
                    worstFitIndex = i;
                }
            }
        }

        int allocatedIndex = -1;
        if (allocationStrategy == 'F' && firstFitIndex != -1) {
            allocatedIndex = firstFitIndex;
        } else if (allocationStrategy == 'B' && bestFitIndex != -1) {
            allocatedIndex = bestFitIndex;
        } else if (allocationStrategy == 'W' && worstFitIndex != -1) {
            allocatedIndex = worstFitIndex;
        }

        if (allocatedIndex != -1) {
            // Split the free region
            MemoryRegion& freeRegion = memoryRegions[allocatedIndex];
            MemoryRegion allocatedRegion(freeRegion.startAddress, size, processName);
            freeRegion.startAddress += size;
            freeRegion.size -= size;
            memoryRegions.insert(memoryRegions.begin() + allocatedIndex, allocatedRegion);

            // Remove the free region if its size becomes 0
            if (freeRegion.size == 0) {
                memoryRegions.erase(memoryRegions.begin() + allocatedIndex + 1);
            }

            sort(memoryRegions.begin(), memoryRegions.end(), compareRegions);
            cout << "Allocated " << size << " bytes for process " << processName << " at address " << allocatedRegion.startAddress << endl;
        } else {
            cout << "Error: Not enough contiguous memory for process " << processName << " (" << size << " bytes) using " << allocationStrategy << " strategy." << endl;
        }
    }

    void releaseMemory(string processName) {
        for (auto it = memoryRegions.begin(); it != memoryRegions.end(); ++it) {
            if (it->processName == processName) {
                cout << "Releasing memory for process " << processName << " (size: " << it->size << " bytes, address: " << it->startAddress << ")" << endl;
                it->processName = ""; // Mark the region as free

                // Merge adjacent free regions
                auto prevIt = prev(it);
                if (prevIt != memoryRegions.end() && prevIt->processName.empty()) {
                    it->startAddress = prevIt->startAddress;
                    it->size += prevIt->size;
                    memoryRegions.erase(prevIt);
                    it = prev(it); // Update iterator after deletion
                }

                auto nextIt = next(it);
                if (nextIt != memoryRegions.end() && nextIt->processName.empty()) {
                    it->size += nextIt->size;
                    memoryRegions.erase(nextIt);
                }
                return;
            }
        }
        cout << "Error: Process " << processName << " not found in memory." << endl;
    }

    void compactMemory() {
        vector<MemoryRegion> newRegions;
        int currentAddress = 0;
        int freeSpace = 0;

        // Move allocated regions to the beginning of memory
        for (const auto& region : memoryRegions) {
            if (!region.processName.empty()) {
                newRegions.push_back(MemoryRegion(currentAddress, region.size, region.processName));
                currentAddress += region.size;
            } else {
                freeSpace += region.size;
            }
        }

        // Add a single free region at the end if there is free space
        if (freeSpace > 0) {
            newRegions.push_back(MemoryRegion(currentAddress, freeSpace));
        }

        memoryRegions = newRegions;
        cout << "Memory compaction completed." << endl;
    }

    void reportStatus() const {
        cout << "\nMemory Status:\n";
        for (const auto& region : memoryRegions) {
            cout << "Address [" << region.startAddress << ":" << region.startAddress + region.size - 1 << "] ";
            if (region.processName.empty()) {
                cout << "Unused (" << region.size << " bytes)\n";
            } else {
                cout << "Process " << region.processName << " (" << region.size << " bytes)\n";
            }
        }
        cout << "Total memory: " << totalMemorySize << " bytes\n";
    }

private:
    int totalMemorySize;
    vector<MemoryRegion> memoryRegions;
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <total_memory_size_in_bytes>" << endl;
        return 1;
    }

    int totalMemory = stoi(argv[1]);
    MemoryAllocator allocator(totalMemory);

    string command;
    while (true) {
        cout << "allocator> ";
        cin >> command;

        if (command == "RQ") {
            string processName;
            int size;
            char strategy;
            cin >> processName >> size >> strategy;
            allocator.requestMemory(size, processName, strategy);
        } else if (command == "RL") {
            string processName;
            cin >> processName;
            allocator.releaseMemory(processName);
        } else if (command == "C") {
            allocator.compactMemory();
        } else if (command == "STAT") {
            allocator.reportStatus();
        } else if (command == "X") {
            break;
        } else {
            cout << "Invalid command. Available commands: RQ, RL, C, STAT, X" << endl;
        }
    }

    return 0;
}
