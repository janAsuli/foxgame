#include <ctime>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>

import Bag;
import Board;
import Tile;

// Runs a game, and returns whether the player won
bool runGame(std::mt19937_64& rng) {
    Board board;
    Bag bag(rng);
    while (!bag.isEmpty()) {
        board.placeTile(rng, bag);
        if (board.hasFox()) {
            return false;
        }
    }
    return true;
}

static int totalWins = 0;
static int totalLosses = 0;
static std::mutex resultsLock;

void runTask(int seed, int count, int threadCount, int threadI) {
    auto rng = std::mt19937_64(seed + threadI);
    int wins = 0;
    int losses = 0;
    for (int i = threadI; i < count; i += threadCount) {
        if (runGame(rng)) {
            wins++;
        } else {
            losses++;
        }
    }
    std::lock_guard<std::mutex> lock(resultsLock);
    totalWins += wins;
    totalLosses += losses;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: foxgame <N>" << std::endl;
        return -1;
    }
    int x = std::stoi(argv[1]);
    auto threadCount = std::thread::hardware_concurrency();
    std::vector<std::thread> threadPool;
    threadPool.reserve(threadCount);
    int seed = std::time(nullptr);
    for (int i = 0; i < threadCount; i++) {
        threadPool.push_back(std::thread(runTask, seed, x, threadCount, i));
    }
    for (auto& thread: threadPool) {
        thread.join();
    }
    std::cout << "Wins: " << totalWins << ", Losses: " << totalLosses << std::endl;
}
